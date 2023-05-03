#include "FSM.h"
#include "mcc_generated_files/mcc.h"
#include <stdio.h>

void Iniciarlizar(variable* est){
    
    for(int i=0;i<4;i++){
      est->add[i]=0;
    }
    est->estados=1;
    est->wb_val[0]=0;
    est->rs_num[0]=0;
    est->ws_data[0]=0;
    est->lectura_add=0;
    est->lectura_data=0;
    est->flag=0;
    for(int j=0;j<4;j++){
      est->instruccion[j]=0;
    }

}


void lectura(char lectura,variable* est){
	
	switch(est->estados){
		
		case(1):            
            if(lectura=='R'){
            //UART1_Write(lectura);
			est->estados=2;
			}
            
            else if(lectura=='W'){
            //UART1_Write(lectura);
			est->estados=3;	            
            }
            
            else{
            //UART1_Write('E');
            //UART1_Write('R');
            //UART1_Write('R');
            est->estados=1;
            }        
        break;
	
        case(2):            
            if(lectura=='B'){
                //UART1_Write(lectura);
                est->lectura_add=0;
                est->estados=4;
            }
            
            else if(lectura=='S'){
                //UART1_Write(lectura);
                est->flag=0;
                est->lectura_add=0;
                est->estados=5;
            }
            
            else{
                //UART1_Write('E');
                //UART1_Write('R');
                //UART1_Write('R');
                est->estados=1;
            }     
        break;

        case(3):
            if(lectura=='B'){
                //UART1_Write(lectura);
                est->flag=0;
                est->lectura_add=0;
                est->lectura_data=0;
                est->estados=6;
            }
            
            else if(lectura=='S'){
                //UART1_Write(lectura);
                est->contador=0;
                est->flag=0;
                est->lectura_add=0;
                est->lectura_data=0;
                est->estados=7;    
            }
            
            else{
                //UART1_Write('E');
                //UART1_Write('R');
                //UART1_Write('R');
                est->estados=1;
            }
        break;
	
        case(4):
            if(est->lectura_add<3){
                est->add[est->lectura_add]=lectura;
                est->lectura_add=est->lectura_add+1;
                //UART1_Write(lectura);
                //UART1_Write(est->lectura_add);
            }
            
            else if(est->lectura_add==3){
                est->add[est->lectura_add]=lectura;
                est->lectura_add=est->lectura_add+1;
                //UART1_Write(lectura);
                est->instruccion[0]=1;
                est->estados=8;
            }

            else{
                //UART1_Write('E');
                //UART1_Write('R');
                //UART1_Write('R');
                est->lectura_add=0;
                est->estados=1;
            }
        break;
   
        case(5):
            if(est->flag==0){
                if(est->lectura_add<3){
                est->add[est->lectura_add]=lectura;
                est->lectura_add=est->lectura_add+1;
                //UART1_Write(lectura);
                //UART1_Write(est->lectura_add);
                }
                
                else if(est->lectura_add==3){
                    est->add[est->lectura_add]=lectura;
                    est->lectura_add=est->lectura_add+1;
                    //UART1_Write(lectura);
                    est->instruccion[0]=1;
                }
                
                else if(lectura==','){
                //UART1_Write(lectura);
                est->flag=1;
                }
            }
            else if(est->flag==1){
                if(est->lectura_data==0){
                    if(lectura<=57){
                    est->rs_num[0]=16*(lectura-48);
                }
                else if(lectura>57){
                    est->rs_num[0]=16*(lectura-55);
                }
                est->lectura_data=est->lectura_data+1;	
                //UART1_Write(lectura);
                }
                else if(est->lectura_data==1){
                    if(lectura<=57){
                    est->rs_num[0]+=(lectura-48);
                    }
                    else if(lectura>57){
                        est->rs_num[0]+=(lectura-55);
                    }
                    est->flag=0;
                    est->instruccion[1]=1;
                    est->estados=8; 
                    //UART1_Write(lectura);
                }

            }
            else{
                //UART1_Write('E');
                //UART1_Write('R');
                //UART1_Write('R');
                est->estados=1;
                est->lectura_data=0;
                est->contador=0;
                est->flag=0;
            }
        break;
   
        case(6):
            if(est->flag == 0){
                if(est->lectura_add<3){
                    est->add[est->lectura_add]=lectura;
                    est->lectura_add=est->lectura_add+1;
                    //UART1_Write(lectura);
                    //UART1_Write(est->lectura_add);
                }
                else if(est->lectura_add==3){
                    est->add[est->lectura_add]=lectura;
                    est->lectura_add=est->lectura_add+1;
                    //UART1_Write(lectura);
                    est->instruccion[0]=1;
                }        
                else if(lectura==','){
                    //UART1_Write(lectura);
                    est->flag=1;
                }             
            }
            else if(est->flag==1){
                if(est->lectura_data==0){
                    if(lectura<=57){
                        est->wb_val[0]=16*(lectura-48);
                    }
                    
                    else if(lectura>57){
                        est->wb_val[0]=16*(lectura-55);
                    }
		    	    
                    est->lectura_data=est->lectura_data+1;	
                    //UART1_Write(lectura);
                }
                else if(est->lectura_data==1){
                    if(lectura<=57){
                        est->wb_val[0]+=(lectura-48);
                    }
                    else if(lectura>57){
                        est->wb_val[0]+=(lectura-55);
                    }
                    //UART1_Write(lectura);
                    est->flag=0;
                    est->lectura_data=0;
                    est->instruccion[2]=1;
                    est->estados=8;
                }
            }
            else{
                //UART1_Write('E');
                //UART1_Write('R');
                //UART1_Write('R');
                est->estados=1;
                est->lectura_data=0;
                est->contador=0;
                est->flag=0;
            }
        break;
	
        case(7): 
            if(est->flag == 0){
                if(est->lectura_add<3){
                    est->add[est->lectura_add]=lectura;
                    est->lectura_add=est->lectura_add+1;
                    //UART1_Write(lectura);
                    //UART1_Write(est->lectura_add);
                }
                
                else if(est->lectura_add==3){
                    est->add[est->lectura_add]=lectura;
                    est->lectura_add=est->lectura_add+1;
                    //UART1_Write(lectura);
                    est->instruccion[0]=1;
                }
                
                else if(lectura==','){
                    //UART1_Write(lectura);
                    est->flag=1;
                }
            }
            else if(est->flag==1){
                if(est->lectura_data<15){
                    if(est->contador==0){	              
                        if(lectura<=57){
                            est->ws_data[est->lectura_data]=16*(lectura-48);
                        }
                        else if(lectura>57){
                            est->ws_data[est->lectura_data]=16*(lectura-55);
                        }
                        est->contador=est->contador+1;
                        //UART1_Write(lectura);
                    }
                    else if(est->contador==1){
                        if(lectura<=57){
                            est->ws_data[est->lectura_data]+=(lectura-48);
                        }
                        else if(lectura>57){
                            est->ws_data[est->lectura_data]+=(lectura-55);
                        }
                        est->contador=est->contador+1;
                        //UART1_Write(lectura);  
                        //UART1_Write(est->contador);
                    }
                    else if(est->contador==2){
                        if(lectura==','){
                            //UART1_Write(lectura);
                            est->contador=0;
                            est->lectura_data++;
                        }
                        else{
                            //UART1_Write('E');
                            //UART1_Write('R');
                            //UART1_Write('R');
                            est->estados=1;
                            est->lectura_data=0;
                            est->contador=0;
                            est->lectura_data=0;
                            est->flag=0;
                        }
                    }
                }
                else if(est->lectura_data>=15){
                    if(est->contador==0){	              
                        if(lectura<=57){
                            est->ws_data[est->lectura_data]=16*(lectura-48);
                        }
                        else if(lectura>57){
                            est->ws_data[est->lectura_data]=16*(lectura-55);
                        }   
                        est->contador=est->contador+1;
                        //UART1_Write(lectura);
                    }
                    else if(est->contador==1){
                        if(lectura<=57){
                            est->ws_data[est->lectura_data]+=(lectura-48);
                        }
                        else if(lectura>57){
                            est->ws_data[est->lectura_data]+=(lectura-55);
                        }
                        est->contador=est->contador+1;
                        //UART1_Write(lectura);  
                        //UART1_Write(est->contador);
                    }
                    else if(est->contador==2){
                        est->lectura_data=0;
                        est->flag=0;
                        est->instruccion[3]=1;
                        est->estados=8;
                    }
                    else{
                        //UART1_Write('E');
                        //UART1_Write('R');
                        //UART1_Write('R');
                        est->estados=1;
                        est->lectura_data=0;
                        est->contador=0;
                        est->lectura_data=0;
                        est->flag=0;
                    }             
                }
            }
            else{
                //UART1_Write('E');
                //UART1_Write('R');
                //UART1_Write('R');
                est->estados=1;
                est->lectura_add=0;
                est->lectura_data=0;
                est->contador=0;
                est->flag=0;
            }
        break;     
	    
        case(8):
            if(lectura==35){
                //UART1_Write('#');
                //UART1_Write('F');
                //UART1_Write('I');
                //UART1_Write('N');
                //UART1_Write('\n');
                est->estados=1;
            } 	
        break;
    }
}
