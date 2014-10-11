

HEADERS		= myls.h

C_SRCS		= myls.c buildFileInfoTable.c displayFileInfo.c \
		  displayPermissions.c displayOwnerName.c nameSortDescending.c \
		  mtimeSortAscending.c

ASM_SRCS	= displayGroupName.s mtimeSortDescending.s nameSortAscending.s

C_OBJS		= myls.o buildFileInfoTable.o displayFileInfo.o \
		  displayPermissions.o displayOwnerName.o nameSortDescending.o \
		  mtimeSortAscending.o

ASM_OBJS	= displayGroupName.o mtimeSortDescending.o nameSortAscending.o \

OBJS		= ${C_OBJS} ${ASM_OBJS}

EXE		= myls



GCC		= gcc
ASM		= ${GCC}
LINT		= lint

GCC_FLAGS	= -c -g -W -Wall -D__EXTENSIONS__
LINT_FLAGS1	= -c -err=warn
LINT_FLAGS2	= -u -err=warn
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -W -Wall



.s.o:
	@echo "Assembling each assembly source file separately ..."
	${ASM} ${ASM_FLAGS} $<
	@echo ""

.c.o:
	@echo "Linting each C source file separately ..."
	${LINT} ${LINT_FLAGS1} $<
	@echo ""
	@echo "Compiling each C source file separately ..."
	${GCC} ${GCC_FLAGS} $<
	@echo ""



${EXE}:	${OBJS}
	@echo "2nd phase lint on all C source files ..."
	${LINT} ${LINT_FLAGS2} *.ln
	@echo ""
	@echo "Linking all object modules ..."
	${GCC} -o ${EXE} ${LD_FLAGS} ${OBJS}
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}




clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o ${EXE} *.ln core a.out
	@echo ""
	@echo "Clean."

new:
	make clean
	make
