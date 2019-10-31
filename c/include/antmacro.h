#ifndef ANTMACRO_H
#define ANTMACRO_H

#ifdef LIBANT_DEBUG

#define ENDL "\n"

#define ANSI_RED "\033[31;1;4m"
#define ANSI_BLUE "\033[34;1;1m"
#define ANSI_YELLOW "\033[33;1;1m"
#define ANSI_GREEN "\033[92;1;1m"
#define ANSI_END "\033[0m"

#define ERROR(tok) ANSI_RED tok ANSI_END
#define TRACE(tok) ANSI_BLUE tok ANSI_END
#define DEBUG(tok) ANSI_YELLOW tok ANSI_END
#define IO_OK(tok) ANSI_GREEN tok ANSI_END

#define ERRORLN(tok) ERROR(tok) ENDL
#define TRACELN(tok) TRACE(tok) ENDL
#define DEBUGLN(tok) DEBUG(tok) ENDL
#define IO_OKLN(tok) IO_OK(tok) ENDL

#endif

#define str(x) #x
#define xstr(x) str(x)

#endif
