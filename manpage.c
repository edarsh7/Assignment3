
/*********************************************************************
 *
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ***********************************************************************/

#include "manpage.h"

/*
 * See manpage.h for details.
 *
 * As supplied, shows random single messages.
 */
void manpage() 
{
  int pid = getParagraphId(); // pid = 'Paragraph Id"
  int pid2 = getParagraphId();
  int pid3 = getParagraphId(); // pid = 'Paragraph Id"
  int pid4 = getParagraphId();
  int pid5 = getParagraphId(); // pid = 'Paragraph Id"
  int pid6 = getParagraphId();
  int pid7 = getParagraphId(); // pid = 'Paragraph Id"
  printf("para id: %d, %d, %d, %d, %d, %d, %d, %d \n", pid, pid2, pid3, pid4, pid5, pid6, pid7);
  showParagraph();

}
