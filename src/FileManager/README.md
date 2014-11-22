Moonlight Desktop Environment File Manager
===========================================

This modules provides a File Manager for the DE.


In order to ease the analisys and maintenaince the module was divided in a set of 
subsystems. Each handle a set of functionalities and provides an interface for 
the rest of the system in a way of services.

File System Access
==================
Resposabilities:
    * Browse local file system.
    * Browse remote file systems supported by gvfs.
    * Virtual representation of the computer that conects all the FS mounted.
    * Access local and remote files content.

Service Interface: IFileSystemService
