testall.bat is a MSDOS batch file to test the routines.
It should be easily modified to check on any system.

malloc.xrf is a file with long lines, to test the extension of the
input buffers.

The whole point is that ggets (and fggets) allows the easy usage
of the evil gets() routine, without the insecurities.  They return
an allocated buffer holding the complete input line, with the
terminal \n removed, and suitable for output via puts().  They
will never create a buffer overrun.

The fact that no storage is supplied to them should emphasize the
fact that the lines returned need to eventually be freed.

They return 0 for success, else EOF for file error or a positive
value for memory allocation error.  Normally the line storage 
pointer will be set to NULL for an error, but under some circumstances
a partial line may be returned.  The pointer is set to the allocated
storage, which has been cut back to the minimum needed.  THERE IS
NO SPARE SPACE for extending the returned lines.  However, their
space may be extended via realloc().

The only thing of eventual use is the ggets.* files.

The two test files tggets and freverse will give some idea of usage.

I have put this in the public domain.  Use as you will. I would
appreciate attribution when used.

I can be reached at <mailto:cbfalconer@maineline.net>

These files are mounted in the download section at:
  <http://cbfalconer.home.att.net>
  
Another approach by Richard Heathfield can be found at:
  <http://www.cpax.org.uk/prg/writings/fgetdata.php>
  
2002-06-22
2002-06-26 revised prototype, error conditions.
2002-06-14 simplified implementation uses getc, not fgets.
2002-12-02 Revised this readme.txt file to reference fgetdata
           and update the URLs.
