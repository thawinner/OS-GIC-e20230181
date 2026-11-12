# Lab 3 — Wildcards, Hard Links and Symbolic Links: individual report

- Student name/ID: YOUR NAME / e20230181
- Ubuntu username: gic-tha-winner
- My values (`oslab values lab3`): name = tiger, tag = saved, v1 = 306, v2 = 356
- Files: `evidence/wildcards.txt`, `evidence/links.txt`, `evidence/replacement.txt`, `evidence/checkpoint.txt`

## What I Saw

| State | What `cat` printed for the hard link | What `cat` printed for the symbolic link | What `readlink` printed |
|---|---|---|---|
| Before the rename | version 306 | version 306 | tiger.txt |
| After the rename, before the repair | version 306 | cat: tiger-soft.txt: No such file or directory | tiger.txt |
| After a new file took the old name | version 306 | version 356 | tiger.txt |
| After my repair | version 306 | version 306 | tiger-saved.txt |

My repair (the two commands I wrote):

## Explanation

A hard link points to an inode, so it stays with the old file, but a symbolic link stores a path, so it follows the new file. My report tiger-saved.txt and tiger-hard.txt share inode 19142246, so the hard link still read version 306 after the rename. The new tiger.txt got a different inode, 19143085, so it is a separate file with version 356. tiger-soft.txt (inode 19143083) only stores the text tiger.txt, so when the new file took that name, the soft link opened the new file and read version 356.

## What My Tests Do Not Prove

cat only shows the content of a file, so it cannot prove that two names are the same file, because two different files can hold the same text. Only ls -li shows the inode numbers, and only the same inode number proves it is one file.

## AI Note (optional)

The AI told me the repaired link must store only tiger-saved.txt, because the target is read from the folder of the link. I tested it with readlink and cat, and the link printed version 306.
