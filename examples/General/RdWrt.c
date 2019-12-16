/********************************************************************/
/*              Read and Write to an Instrument Example             */
/*                                                                  */
/* This code demonstrates synchronous read and write commands to a  */
/* GPIB, serial or message-based VXI instrument using VISA.         */
/*                                                                  */
/* The general flow of the code is                                  */
/*      Open Resource Manager                                       */
/*      Open VISA Session to an Instrument                          */
/*      Write the Identification Query Using viWrite                */
/*      Try to Read a Response With viRead                          */
/*      Close the VISA Session                                      */
/********************************************************************/

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
/* Functions like strcpy are technically not secure because they do */
/* not contain a 'length'. But we disable this warning for the VISA */
/* examples since we never copy more than the actual buffer size.   */
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "visa.h"

static ViSession defaultRM;
static ViSession instr;
static ViStatus status; 
static ViUInt32 retCount;
static ViUInt32 writeCount;
static unsigned char buffer[100];
static char stringinput[512];
static char retString[100];

/*
* In every source code or header file that you use it is necessary to prototype
* your VISA variables at the beginning of the file. You need to declare the VISA
* session, VISA integers, VISA strings, VISA pointers, and VISA floating variables. 
* Remember that if you are prototyping variables that are to be used as part of the
* VISA session that need this prototyping. As an example, above retCount has been
* prototyped as a static variable to this particular module.   It is an integer of
* bit length 32. If you are uncertain how to declare your VISA prototypes refer
* to the VISA help under the Section titled Type Assignments Table. The VISA
* help is located in your NI-VISA directory or folder.
*/


char* getReadValue(const char *str)
{
   const char separator = ' ';
   char* sep = strchr(str, separator);

   if (sep != NULL) 
   {
      *sep = '\0';
      return (sep+1);
   }
   return '\0';

}


int main(void)
{
   memset(buffer, 0, sizeof(buffer));
   memset(retString, 0, sizeof(retString));
    /*
     * First we must call viOpenDefaultRM to get the resource manager
     * handle.  We will store this handle in defaultRM.
     */
   status=viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)
   {
      printf("Could not open a session to the VISA Resource Manager!\n");
      exit (EXIT_FAILURE);
   } 
                                                                         
    /*
     * Now we will open a VISA session to a device at Primary Address 2.
     * You can use any address for your instrument. In this example we are 
     * using GPIB Primary Address 2.
     *
     * We must use the handle from viOpenDefaultRM and we must   
     * also use a string that indicates which instrument to open.  This
     * is called the instrument descriptor.  The format for this string
     * can be found in the NI-VISA User Manual.
     * After opening a session to the device, we will get a handle to 
     * the instrument which we will use in later VISA functions.  
     * The two parameters in this function which are left blank are
     * reserved for future functionality.  These two parameters are 
     * given the value VI_NULL.
     *
     * This example will also work for serial or VXI instruments by changing 
     * the instrument descriptor from GPIB0::2::INSTR to ASRL1::INSTR or
     * VXI0::2::INSTR depending on the necessary descriptor for your 
     * instrument.
     */
   status = viOpen (defaultRM,  "GPIB0::11::INSTR", VI_NULL, VI_NULL, &instr);
   if (status < VI_SUCCESS)  
   {
        printf ("Cannot open a session to the device.\n");
         status = viClose(instr);
         status = viClose(defaultRM);

         return 0;
   }
  
    /*
     * Set timeout value to 5000 milliseconds (5 seconds).
     */ 
   status = viSetAttribute (instr, VI_ATTR_TMO_VALUE, 5000);
  
    /*
     * At this point we now have a session open to the instrument at
     * Primary Address 2.  We can use this session handle to write 
     * an ASCII command to the instrument.  We will use the viWrite function
     * to send the string "*IDN?", asking for the device's identification.  
     */
   strcpy(stringinput,"*IDN?");
   status = viWrite (instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
   if (status < VI_SUCCESS)  
   {
      printf("Error writing to the device\n");
         status = viClose(instr);
         status = viClose(defaultRM);

         return 0;
   }
     
    /*
     * Now we will attempt to read back a response from the device to
     * the identification query that was sent.  We will use the viRead
     * function to acquire the data.  We will try to read back 100 bytes.
     * After the data has been read the response is displayed.
     */
   status = viRead (instr, buffer, 100, &retCount);
   if (status < VI_SUCCESS) 
   {
      printf("Error reading a response from the device\n");
   }
   else
   {
      printf("Data read: %*s\n",retCount,buffer);
   }

   // strcpy(stringinput, "MEASUrement:IMMed:TYPe FREQuency");
   // status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   // strcpy(stringinput, "MEASUrement:IMMed:SOURCE[1] CH1");
   // status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   // strcpy(stringinput, "MEASUrement:IMMed?");
   // status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   // status = viRead(instr, buffer, 100, &retCount);
   // memset(buffer, 0, sizeof(buffer));
   // printf("Data read: %*s\n", retCount, buffer);
   // memset(buffer, 0, sizeof(buffer));

   // strcpy(stringinput, "AUTOset EXECUTE");
   // status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   // strcpy(stringinput, "CH1:SCALE 500e-3");
   // status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   strcpy(stringinput, "DATA:SOU CH1");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   strcpy(stringinput, "DATA:WIDTH 1");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   strcpy(stringinput, "DATA:ENC RPB");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   strcpy(stringinput, "WFMPRE:YMULT?");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
   memset(buffer, 0, sizeof(buffer));
   status = viRead(instr, buffer, 100, &retCount);
   printf("Data read: %*s\n", retCount, buffer);
   // strncpy(getReadValue(buffer), retString, sizeof(retString));
   // // retString = getReadValue(buffer);
   // printf("Ret string read: %s", retString);



   strcpy(stringinput, "WFMPRE:YZERO?");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
   memset(buffer, 0, sizeof(buffer));
   status = viRead(instr, buffer, 100, &retCount);
   printf("Data read: %*s\n", retCount, buffer);


   strcpy(stringinput, "WFMPRE:YOFF?");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
   memset(buffer, 0, sizeof(buffer));
   status = viRead(instr, buffer, 100, &retCount);
   printf("Data read: %*s\n", retCount, buffer);

   strcpy(stringinput, "WFMPRE:XINCR?");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);
   memset(buffer, 0, sizeof(buffer));
   status = viRead(instr, buffer, 100, &retCount);
   printf("Data read: %*s\n", retCount, buffer);

   strcpy(stringinput, "CURVE?");
   status = viWrite(instr, (ViBuf)stringinput, (ViUInt32)strlen(stringinput), &writeCount);

   unsigned char ret[20*1024];
   
   
   int ret_size = (int)(sizeof(ret)/sizeof(ret[0]));

   status = viRead(instr, ret, ret_size, &retCount);

   unsigned char* p = ret + 13;

   int new_ret_size = retCount - 13;
   int k;
   printf("Data is: \n");
   float data[retCount];
   int offset = 128;
   float mult = 20.0000E-3f;
   float xincr = 80e-9f;
   float yzero = 0.0f;
   float time[retCount];

   int val;
   for (k = 0; k < retCount; k++)
   {
      /** data[k] = *p; **/

      // float val;
      
      // memcpy(&val, p, sizeof(float));
      // int byte_val = ((int) *p) - offset;
      // memcpy(&val, p, 2*sizeof(unsigned char));
      // printf("%d, ", val);
      data[k] = (((int)*p - offset) * mult) + yzero;
      time[k] = (float)(k * xincr);
      // float val;
      // val = *(float*)p;
      // float val = mult * (float)((byte_int_val - offset));
      // float 
      // float val = atof(byte_val);
      // printf("%2.0f,", atof(byte_val));
      p++;
   }
   printf("\n\nTime (s) | Voltage (V)\n\n");
   for (k = 0; k < retCount; k++)
   {
      printf("%0.10f  s | %0.3f V\n", time[k], data[k]);
      // /** printf("%d,", data[k]); **/
   }
   printf("\n");


    
         status = viClose(instr);
         status = viClose(defaultRM);

         return 0;
   /*
    * Now we will close the session to the instrument using
    * viClose. This operation frees all system resources.                     
    */
    /**
Close:
   printf("Closing Sessions\nHit enter to continue.");
   fflush(stdin);
   getchar();  
   status = viClose(instr);
   status = viClose(defaultRM);

   return 0;
**/
}
