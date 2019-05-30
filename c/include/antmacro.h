#ifndef ANTMACRO_H
#define ANTMACRO_H

#ifdef LIBANT_DEBUG
#define ANSI_RED "\033[31;1;4m"
#define ANSI_END "\033[0m"
#define DEBUG(tok) ANSI_RED tok ANSI_END
#endif

#define str(x) #x
#define xstr(x) str(x)

#endif