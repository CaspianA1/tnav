# TNAV

### An application-embeddable file selection tool.

Here's what that means:

- Sometimes, an app might prompt you to open a file, and open the finder for this.
- I haven't seen an equivalent for any CLI apps, so I made this!

#### Here's how to use it:

```c
char* file = select_file();
// do stuff with the file
free(file);
```

- This will bring up a screen to navigate around in the filesystem.
- The up and down arrows move you around, and the right arrow moves you into a new directory.
- Pressing enter selects that file.
- I hope that you find a good use for this! It was really fun to make.