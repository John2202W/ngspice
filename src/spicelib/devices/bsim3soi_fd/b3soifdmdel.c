/**********
Copyright 1999 Regents of the University of California.  All rights reserved.
Author: 1998 Samuel Fung, Dennis Sinitsky and Stephen Tang
File: b3soifdmdel.c          98/5/01
**********/


#include "ngspice.h"
#include <stdio.h>
#include "b3soifddef.h"
#include "sperror.h"
#include "suffix.h"

int
B3SOIFDmDelete(inModel,modname,kill)
GENmodel **inModel;
IFuid modname;
GENmodel *kill;
{
B3SOIFDmodel **model = (B3SOIFDmodel**)inModel;
B3SOIFDmodel *modfast = (B3SOIFDmodel*)kill;
B3SOIFDinstance *here;
B3SOIFDinstance *prev = NULL;
B3SOIFDmodel **oldmod;

    oldmod = model;
    for (; *model ; model = &((*model)->B3SOIFDnextModel)) 
    {    if ((*model)->B3SOIFDmodName == modname || 
             (modfast && *model == modfast))
	     goto delgot;
         oldmod = model;
    }
    return(E_NOMOD);

delgot:
    *oldmod = (*model)->B3SOIFDnextModel; /* cut deleted device out of list */
    for (here = (*model)->B3SOIFDinstances; here; here = here->B3SOIFDnextInstance)
    {    if(prev) FREE(prev);
         prev = here;
    }
    if(prev) FREE(prev);
    FREE(*model);
    return(OK);
}



