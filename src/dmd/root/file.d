/**
 * Compiler implementation of the D programming language
 * http://dlang.org
 *
 * Copyright: Copyright (C) 1999-2019 by The D Language Foundation, All Rights Reserved
 * Authors:   Walter Bright, http://www.digitalmars.com
 * License:   $(LINK2 http://www.boost.org/LICENSE_1_0.txt, Boost License 1.0)
 * Source:    $(LINK2 https://github.com/dlang/dmd/blob/master/src/dmd/root/file.d, root/_file.d)
 * Documentation:  https://dlang.org/phobos/dmd_root_file.html
 * Coverage:    https://codecov.io/gh/dlang/dmd/src/master/src/dmd/root/file.d
 */

module dmd.root.file;

import core.stdc.errno;
import core.stdc.stdio;
import core.stdc.stdlib;
import core.sys.posix.fcntl;
import core.sys.posix.unistd;
import core.sys.windows.winbase;
import core.sys.windows.winnt;
import dmd.root.filename;
import dmd.root.rmem;
import dmd.utils;

/// Owns a (rmem-managed) file buffer.
struct FileBuffer
{
    ubyte[] data;

    this(this) @disable;

    ~this() pure nothrow
    {
        mem.xfree(data.ptr);
    }

    /// Transfers ownership of the buffer to the caller.
    ubyte[] extractData() pure nothrow @nogc @safe
    {
        auto result = data;
        data = null;
        return result;
    }

    extern (C++) static FileBuffer* create()
    {
        return new FileBuffer();
    }
}

///
struct File
{
    ///
    static struct ReadResult
    {
        bool success;
        FileBuffer buffer;

        /// Transfers ownership of the buffer to the caller.
        ubyte[] extractData() pure nothrow @nogc @safe
        {
            return buffer.extractData();
        }
    }

nothrow:
    /// Read the full content of a file.
    extern (C++) static ReadResult read(const(char)* name)
    {
        ReadResult result;

        import core.stdc.string : strcmp;
        if (strcmp(name, "__main.d") == 0)
        {
            /* "Read" the dummy main.d file */
            result.success = true;
            result.buffer.data = cast(ubyte[]) xarraydup("int main(){return 0;}");
            return result;
        }
        if (strcmp(name, "__stdin.d") == 0)
        {
            /* Read from stdin */
            enum bufIncrement = 128 * 1024;
            size_t pos = 0;
            size_t sz = bufIncrement;

            ubyte* buffer = null;
            L1: for (;;)
            {
                buffer = cast(ubyte*)mem.xrealloc(buffer, sz + 2); // +2 for sentinel
                if (!buffer)
                    break L1;

                // Fill up buffer
                do
                {
                    assert(sz > pos);
                    size_t rlen = fread(buffer + pos, 1, sz - pos, stdin);
                    pos += rlen;
                    if (ferror(stdin))
                    {
                        printf("\tread error, errno = %d\n", errno);
                        break L1;
                    }
                    if (feof(stdin))
                    {
                        // We're done
                        assert(pos < sz + 2);
                        buffer[pos] = '\0';
                        buffer[pos + 1] = '\0';
                        result.success = true;
                        result.buffer.data = buffer[0 .. pos];
                        return result;
                    }
                } while (pos < sz);

                // Buffer full, expand
                sz += bufIncrement;
            }
            mem.xfree(buffer);
            return result;
        }

        version (Posix)
        {
            size_t size;
            stat_t buf;
            ssize_t numread;
            //printf("File::read('%s')\n",name);
            int fd = open(name, O_RDONLY);
            if (fd == -1)
            {
                //printf("\topen error, errno = %d\n",errno);
                return result;
            }
            //printf("\tfile opened\n");
            if (fstat(fd, &buf))
            {
                printf("\tfstat error, errno = %d\n", errno);
                close(fd);
                return result;
            }
            size = cast(size_t)buf.st_size;
            ubyte* buffer = cast(ubyte*)mem.xmalloc(size + 2);
            if (!buffer)
                goto err2;
            numread = .read(fd, buffer, size);
            if (numread != size)
            {
                printf("\tread error, errno = %d\n", errno);
                goto err2;
            }
            if (close(fd) == -1)
            {
                printf("\tclose error, errno = %d\n", errno);
                goto err;
            }
            // Always store a wchar ^Z past end of buffer so scanner has a sentinel
            buffer[size] = 0; // ^Z is obsolete, use 0
            buffer[size + 1] = 0;
            result.success = true;
            result.buffer.data = buffer[0 .. size];
            return result;
        err2:
            close(fd);
        err:
            mem.xfree(buffer);
            return result;
        }
        else version (Windows)
        {
            DWORD size;
            DWORD numread;

            // work around Windows file path length limitation
            // (see documentation for extendedPathThen).
            HANDLE h = name.toDString.extendedPathThen!
                (p => CreateFileW(p.ptr,
                                  GENERIC_READ,
                                  FILE_SHARE_READ,
                                  null,
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
                                  null));
            if (h == INVALID_HANDLE_VALUE)
                return result;
            size = GetFileSize(h, null);
            ubyte* buffer = cast(ubyte*)mem.xmalloc(size + 2);
            if (!buffer)
                goto err2;
            if (ReadFile(h, buffer, size, &numread, null) != TRUE)
                goto err2;
            if (numread != size)
                goto err2;
            if (!CloseHandle(h))
                goto err;
            // Always store a wchar ^Z past end of buffer so scanner has a sentinel
            buffer[size] = 0; // ^Z is obsolete, use 0
            buffer[size + 1] = 0;
            result.success = true;
            result.buffer.data = buffer[0 .. size];
            return result;
        err2:
            CloseHandle(h);
        err:
            mem.xfree(buffer);
            return result;
        }
        else
        {
            assert(0);
        }
    }

    /// Write a file, returning `true` on success.
    extern (D) static bool write(const(char)* name, const void[] data)
    {
        version (Posix)
        {
            ssize_t numwritten;
            int fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, (6 << 6) | (4 << 3) | 4);
            if (fd == -1)
                goto err;
            numwritten = .write(fd, data.ptr, data.length);
            if (numwritten != data.length)
                goto err2;
            if (close(fd) == -1)
                goto err;
            return true;
        err2:
            close(fd);
            .remove(name);
        err:
            return false;
        }
        else version (Windows)
        {
            DWORD numwritten; // here because of the gotos
            // work around Windows file path length limitation
            // (see documentation for extendedPathThen).
            HANDLE h = name.toDString.extendedPathThen!
                (p => CreateFileW(p.ptr,
                                  GENERIC_WRITE,
                                  0,
                                  null,
                                  CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
                                  null));
            if (h == INVALID_HANDLE_VALUE)
                goto err;

            if (WriteFile(h, data.ptr, cast(DWORD)data.length, &numwritten, null) != TRUE)
                goto err2;
            if (numwritten != data.length)
                goto err2;
            if (!CloseHandle(h))
                goto err;
            return true;
        err2:
            CloseHandle(h);
            DeleteFileA(name);
        err:
            return false;
        }
        else
        {
            assert(0);
        }
    }

    /// ditto
    extern (C++) static bool write(const(char)* name, const(void)* data, size_t size)
    {
        return write(name, data[0 .. size]);
    }

    /// Delete a file.
    extern (C++) static void remove(const(char)* name)
    {
        version (Posix)
        {
            int dummy = .remove(name);
        }
        else version (Windows)
        {
            DeleteFileA(name);
        }
        else
        {
            assert(0);
        }
    }
}
