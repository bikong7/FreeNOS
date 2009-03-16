/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __FILESYSTEM_FILE_H
#define __FILESYSTEM_FILE_H

#include <arch/Process.h>
#include <Types.h>
#include <Error.h>
#include <sys/stat.h>

/**
 * All possible filetypes.
 */
typedef enum FileType
{
    RegularFile         = S_IFREG,
    DirectoryFile       = S_IFDIR,
    BlockDeviceFile     = S_IFBLK,
    CharacterDeviceFile = S_IFCHR,
    SymlinkFile         = S_IFLNK,
    FIFOFile            = S_IFIFO,
}
FileType;

/** File access permissions. */
typedef uint FileMode;

/**
 * Abstracts a file which is opened by a process.
 */
class File
{
    public:
    
	/**
	 * Constructor function.
	 * @param t Type of file.
	 * @param u User identity.
	 * @param g Group identity.
	 */
	File(FileType t = RegularFile, UserID u = ZERO, GroupID g = ZERO)
	    : type(t), size(ZERO), uid(u), gid(g)
	{
	}

	/**
	 * Destructor function.
	 */
	virtual ~File()
	{
	}
    
	/**
	 * Read bytes from the file.
	 * @param buffer Output buffer.
	 * @param size Maximum size to read.
	 * @param offset Offset in the file to read.
	 * @return Number of bytes read on success, Error on failure.
	 */
	virtual Error read(u8 *buffer, Size size, Size offset)
	{
	    return ENOSUPPORT;
	}

	/**
	 * Write bytes to the file.
	 * @param buffer Input buffer.
	 * @param size Maximum size to write.
	 * @param offset Offset in the file to write.
	 * @return Number of bytes written on success, Error on failure.
	 */
	virtual Error write(u8 *buffer, Size size, Size offset)
	{
	    return ENOSUPPORT;
	}
    
	/**
	 * Retrieve file statistics.
	 * @param st Buffer to write statistics to.
	 */
	virtual void status(struct stat *st)
	{
	    st->st_mode = type;
	    st->st_size = size;
	    st->st_uid  = uid;
	    st->st_gid  = gid;
	}
    
    protected:

	/** File of this file. */
	FileType type;
	
	/** Size of the file, in bytes. */
	Size size;
	
	/** Owner of the file. */
	UserID uid;
	
	/** Group of the file. */
	GroupID gid;
};

#endif /* __FILESYSTEM_FILE_H */
