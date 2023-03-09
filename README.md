Readme.nd

March 9, 2023
	Three more just REALLY bad blunders.  All four caused
	by Copy-Paste.  This happens to me all the time.
	Think I'll Learn? NO!

March 8, 2023
	Well, the problem was in the Terminals Set.  Seems that
	I forgot to put 'Epsilon' into that set.  Caused all
	manner of problems, and then when you add another 
	blunder to that which was the routine that got an index
	for a terminal symbol returned 0 even if it did no 
	find that symbol. Zero was the index for an IDENT is
	the test grammar.  Quite a search to find that problem.

March 6, 2023
	Either the First Sets and or the Follow Sets are 
	incorrect.  I am not that bad at writing grammars.
	In particular, the grammar that I wote for a FOR
	statement seems to generate a lot of conflicts even
	when I get it down to the bare bones.  So, back to
	verifying FIRST and FOLLOW.

March 5, 2023
	Getting SO close.

March 4, 2023
	I am in an Iterim Testing phase.  I am generating a list
	of conflicts (I hope) and am using that information to try and
	write a more or less complex grammar.  I fixed some of the
	deficiencies.  Even though I have written code that hopefully
	generates correct info in order to build a parse table does not
	mean that I know how to write grammars. :)  I did get the "Action"
	grammar down to 0 conflicts, but as it turned out the grammar was
	kind of screwy which prompted me to check for undefined and orphandd
	Non Terminals.  Still, I seem to be making progress.

Feb 23, 2023
	The parse table looks like it is being
	generated correctly.  It at least works with
	the simple example that is always used in
	compiler books (In my case, The Dragon Book 2nd edition).
	Next up, generate code.
	By the way, that part is going to be very
	minimal.

Feb 20, 2023
	Something got goofed up.  This time with the project file.  So once 
again, I start over.  Well, not completely.
Created a new project and copied in the files.  Still, I hate it when 
this happens.

Feb 10, 2023
I think I have Follow sets working.  One Issue with
left for test2.gram, 'Assignment' shows up with no
follow set.  You CS students might actually get a C+
when you turn this in as your homework.

Note: For an example grammar with a known follow
set, I get an exact match :)

Feb 8, 2023
I do believe that Creating a first set is now complete.
You CS students might actually get a C on this.

Feb 7, 2023
Still working on creating the First Sets.
There is still one rabit hole to go down yet,
but currently, All the first sets do look correct,
but there is still one last test for first sets that need
to be written.  I would have never guessed just how difficult
this is.
And if you want to turn this project in as your CS home work,
well, you might actually be able to get a C-, but only
if you clean up all the superfulous garbage.

Jan 12, 2023
Debugging the Parser and Lexer.

Jan 13, 2023
Much Better.  Next Up:First and Follow Sets

Jan 20, 2023
I think I am generating the First Sets correctly.
Next up: Follow Sets.  This is going to be
much more difficult.
