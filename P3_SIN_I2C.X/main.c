#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/examples/i2c_simple_example.h"
#include "FSM.h"
#include "cola.h"
#include <stdio.h>

/*
                         Main application
 */
void main(void)
{
    variable est;
    eCola cola;
    uint8_t datosEnvio[18];
    uint8_t datosRecibidos[255];
    char guardar;


    // Initialize the device
    SYSTEM_Initialize();
    
    Iniciarlizar(&est);
    inicie_cola(&cola);
    

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {       
    
      if(UART1_is_rx_ready()){
        guardar=UART1_Read();
        //UART1_Write(guardar);
        cola_add(&cola,guardar);
      }
      if(tam_cola(&cola)>=1){
        lectura(cola_get(&cola),&est);

      }

      if(est.instruccion[0]==1){//RB   
           //UART1_Write('R');
           //UART1_Write('B');
           datosEnvio[0]=(est.add[0]-48)*16;
           datosEnvio[0]=(est.add[1]-48)+datosEnvio[0];
           datosEnvio[1]=(est.add[2]-48)*16;
           datosEnvio[1]=(est.add[3]-48)+datosEnvio[1]; 
           
           //UART1_Write(datosEnvio[0]);
          // UART1_Write(datosEnvio[1]);

           
           i2c_writeNBytes(MEMORYCONFIG,datosEnvio,2);
           i2c_readNBytes(MEMORYCONFIG,datosRecibidos,1);
           
           //UART1_Write(datosRecibidos[0]);
           
           est.instruccion[0]=0;

      }
      else if(est.instruccion[1]==1){//RS
          //UART1_Write('R');
           //UART1_Write('S');
          datosEnvio[0]=(est.add[0]-48)*16;
          datosEnvio[0]=(est.add[1]-48)+datosEnvio[0];
          datosEnvio[1]=(est.add[2]-48)*16;
          datosEnvio[1]=(est.add[3]-48)+datosEnvio[1];
          
          //UART1_Write(datosEnvio[0]);
          //UART1_Write(datosEnvio[1]);
            
          i2c_writeNBytes(MEMORYCONFIG,datosEnvio,2);
          i2c_readNBytes(MEMORYCONFIG,datosRecibidos,est.rs_num[0]);
         
          for(int i=0;i<est.rs_num[0];i++){
          //UART1_Write(datosRecibidos);
        }
          
          est.instruccion[1]=0;

      }
      else if(est.instruccion[2]==1){//WB
          //UART1_Write('W');
           //UART1_Write('B');
          datosEnvio[0]=(est.add[0]-48)*16;
          datosEnvio[0]=(est.add[1]-48)+datosEnvio[0];
          datosEnvio[1]=(est.add[2]-48)*16;
          datosEnvio[1]=(est.add[3]-48)+datosEnvio[1];
          datosEnvio[2]=est.wb_val[0];
          
          //UART1_Write(datosEnvio[0]);
          //UART1_Write(datosEnvio[1]);
          //UART1_Write(datosEnvio[2]);
          
          i2c_writeNBytes(MEMORYCONFIG,datosEnvio,3);        
          i2c_writeNBytes(MEMORYCONFIG,datosEnvio,2);
          i2c_readNBytes(MEMORYCONFIG,datosRecibidos,1);
          est.instruccion[2]=0;

      }
      else if(est.instruccion[3]==1){   //WS
          
          //UART1_Write('W');
           //UART1_Write('s');
          datosEnvio[0]=(est.add[0]-48)*16;
          datosEnvio[0]=(est.add[1]-48)+datosEnvio[0];
          datosEnvio[1]=(est.add[2]-48)*16;
          datosEnvio[1]=(est.add[3]-48)+datosEnvio[1];
          
          for(int i=0;i<16;i++){
              datosEnvio[i+2]=est.ws_data[i];
        }

        i2c_writeNBytes(MEMORYCONFIG,datosEnvio,sizeof(datosEnvio));
        est.instruccion[3]=0;


      }

    }
}
    




/*
 End of File
*/