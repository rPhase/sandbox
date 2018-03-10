#include <unistd.h>
#include <stdint.h>

 uint32_t result;
 uint8_t ch;

 int main(){
 /* 
 do
 {
   result = read(0, &ch, 1);
   if (result)
   {
     if (((ch >= '0') && (ch <= '9')) ||
         ((ch >= 'a') && (ch <= 'f')))
     {
       write(1, &ch, 1);
     }
     else if (((ch >= 'A') && (ch <= 'Z')) ||
              ((ch >= 'a') && (ch <= 'z')))
     {
       write(2, &ch, 1);
     }
     else
     {
       write(3, &ch, 1);
     }
   }
 } while (result);
 */
 
 //do
 do_loop:
   result = read(0, &ch, 1);
   if (!result) goto _endloop;
   
     //if (!(((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')))) goto elseIf1;
     //if (!((ch >= '0') && (ch <= '9')) && !((ch >= 'a') && (ch <= 'f'))) goto elseIf1;
     //if ((!(ch >= '0') || !(ch <= '9')) && !((ch >= 'a') && (ch <= 'f'))) goto elseIf1;
     //if ((!(ch >= '0') || !(ch <= '9')) && (!(ch >= 'a') || !(ch <= 'f'))) goto elseIf1;
     //if (((ch < '0') || (ch > '9')) && ((ch < 'a') || (ch > 'f'))) goto elseIf1;
     if (ch < '0') goto next;
     if (ch > '9') goto next;
     goto write1;
     next:
     //if ((ch < 'a') || (ch > 'f')) goto elseIf1;
     if (ch < 'a') goto elseIf1;
     if (ch > 'f') goto elseIf1;
     write1:
            write(1, &ch, 1);
            goto endIf1;
     elseIf1:
     //if (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z')))
     //if (((ch < 'A') || (ch > 'Z')) && ((ch < 'a') || (ch > 'z'))) goto else2;
     if (ch < 'A') goto next2;
     if (ch > 'Z') goto next2;
     goto write2;
     next2:
     if (ch < 'a') goto else2;
     if (ch > 'z') goto else2;
     write2:
            write(2, &ch, 1);
            goto endIf1;
     
     else2:
          write(3, &ch, 1);
     endIf1:
 //} while (result);
 if (result) goto do_loop;
 _endloop:
	
  return 0;
}
