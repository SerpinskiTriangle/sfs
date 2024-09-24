# DISCLAMER: THIS FILE IS SUBJECT TO CHANGE AS I FIGURE OUT WHAT I'M ACTUALLY DOING, IT SERVES NOT AS DOCUMENTATION, BUT AS A REPLACEMENT FOR MY ABILITY TO REMEMBER WHAT I WANT TO DO

# SFS
## Overview
### What is SFS?
SFS (Simple filesystem) is a filesystem made for SOS with the intent of minimizing complexity at every possible point.
### How?
SFS attempts to achieve maximum simplicity by only implementing 2 kinds of "thing" in the filesystem; data blocks, and metadata blocks, with the latter describing the former.

---

## Implementation
### All your data are file
The first and most important part of SFS is that **everything** in SFS is a file. This includes directories and devices, just like some other, lousier filesystems you may have heard of. The reason behind this is that implementing just 1 kind of construct in the filesystem makes every interation within it generic, which will hopefully continue to neccessetate an extremely minimal amount of support as SOS is developed on top of it.
### (Meta)Data 
All blocks, both metadata and data are exactly 4kib in size, and can never change size.
**Metadata blocks** are composed of the following (in as of yet no particular order):
|Component                                             |Component wight|
|------------------------------------------------------|---------------|
| A filename                                           |64 bytes       |
| A file type                                          |32 bytes       |
| An array of permissions                              |32 bytes       |
| An array of pointers t /o the beginning of data blocks |64 bytes       |
| An array of pointers to the end of data blocks       |64 bytes       |
(All numbers are assuming a 64-bit address space)

The arrays of pointers to the beginnings an ends of data blocks are the core of all metatadata blocks and work by pointing not to individual data blocks, but to *continuous extents of*  data blocks. This allows them to at minimum handle a single data block per pair of pointers in each metadatablock (assuming all are maximally fragmented), and a maximum file size determined by the memory address space of the machinge
