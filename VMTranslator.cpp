#include<bits/stdc++.h>
#include <fstream>
#include<string.h>
#include<dirent.h>

using namespace std;

class codeWriter
{
	ofstream outfile;
	string stemp;
	
	public:
		static int loop;
		static int myvar;
		static int bootvar;
		codeWriter(string otfile,string sname)
		{ stemp = sname;
		 int n = otfile.length();
		 char c_array[n+1];
		 strcpy(c_array,otfile.c_str());
			outfile.open(c_array);
		}
		
		codeWriter(string otfile,string sname,int n)
		{ stemp = sname;
		 int an = otfile.length();
		 char c_array[an+1];
		 strcpy(c_array,otfile.c_str());
			outfile.open(c_array,ios::app);
			
			if(bootvar == 0)
			  write_boot();
		}
		
		
		void write_boot()
		{
			outfile<<"// writing booting program. "<<endl;
			outfile<<"@256"<<endl;
			outfile<<"D = A"<<endl;
			outfile<<"@SP"<<endl;
			outfile<<"M = D"<<endl;
			
			//outfile<<"@Sys.init"<<endl;
		    //         outfile<<"0;JMP"<<endl;
		    write_call("Sys.init","0");
			bootvar++;
		}
		
		void write_goto(string l_name)
		{
			outfile<<"// performing goto "<<l_name<<" operation .. "<<endl;
			outfile<<"@"<<l_name<<endl;
			outfile<<"0;JMP"<<endl;
			
		}
		
		void write_ifgoto(string l_name)
		{
			outfile<<"// performing if-goto "<<l_name<<" operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@"<<l_name<<endl;
		   outfile<<"D;JNE"<<endl;
			
		}
		
		void write_label(string l_name)
		{
			outfile<<"// performing label "<<l_name<<" operation .. "<<endl;
			outfile<<"("<<l_name<<")"<<endl;			
		}
		
		
		void write_call(string f_name,string mynum)
		{
			
			        int numtemp[20];
  				 	int nargs = 0;
	           		int ml =1;
	           		 int m = 0;  				
  				 	for(int k =0; k<mynum.size(); k++)
  				 	 {    if(mynum[k]!=' ' && mynum[k]!='	')
    					 {
    					  numtemp[m] = mynum[k]-48;
    					  m++;
						  }
						}
					
    				for(int k =(m-1); k>=0; k--)
    				{ 
					   nargs = nargs+ numtemp[k]*ml;
    				   ml = ml* 10;
					}
					
					
					 outfile<<"// performing call "<<f_name<<" "<<nargs<<" operation .. "<<endl;
		             outfile<<"@"<<f_name<<"$return."<<myvar<<endl;
		             outfile<<"D = A"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"A = M"<<endl;
		             outfile<<"M = D"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"M = M+1"<<endl;
		             
		             outfile<<"@LCL"<<endl;
		             outfile<<"D = M"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"A = M"<<endl;
		             outfile<<"M = D"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"M = M+1"<<endl;
		             
		             outfile<<"@ARG"<<endl;
		             outfile<<"D = M"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"A = M"<<endl;
		             outfile<<"M = D"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"M = M+1"<<endl;
		             
		             outfile<<"@THIS"<<endl;
		             outfile<<"D = M"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"A = M"<<endl;
		             outfile<<"M = D"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"M = M+1"<<endl;
		             
		             outfile<<"@THAT"<<endl;
		             outfile<<"D = M"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"A = M"<<endl;
		             outfile<<"M = D"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"M = M+1"<<endl;
		            
		             outfile<<"@5"<<endl;
		             outfile<<"D = A"<<endl;
		             outfile<<"@"<<nargs<<endl;
		             outfile<<"D = D+A"<<endl;
		             outfile<<"@SP"<<endl;
		             outfile<<"D = M-D"<<endl;
		             outfile<<"@ARG"<<endl;
		             outfile<<"M = D"<<endl;
		             
		             
		             outfile<<"@SP"<<endl;
		             outfile<<"D = M"<<endl;
		             outfile<<"@LCL"<<endl;
		             outfile<<"M = D"<<endl;
		             
		             outfile<<"@"<<f_name<<endl;
		             outfile<<"0;JMP"<<endl;
		             
		             outfile<<"("<<f_name<<"$return."<<myvar<<")"<<endl;
		           
					myvar++;
		}
		
		
		 void write_function(string f_name,string mynum)
		 {
		 	int numtemp[20];
  				 	int nvars = 0;
	           		int ml =1;
	           		 int m = 0;  				
  				 	for(int k =0; k<mynum.size(); k++)
  				 	 {    if(mynum[k]!=' ' && mynum[k]!='	')
    					 {
    					  numtemp[m] = mynum[k]-48;
    					  m++;
						  }
						}
					
    				for(int k =(mynum.size()-1); k>=0; k--)
    				{ 
					   nvars = nvars+ numtemp[k]*ml;
    				   ml = ml* 10;
					}
					
					
				outfile<<"// performing function "<<f_name<<" "<<nvars<<"operation .. "<<endl;
		        outfile<<"("<<f_name<<")"<<endl;
		        while(nvars--)
		        {
		        	 
				    	outfile<<"@0"<<endl;
				    	outfile<<"D = A"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
				}
		 	
		 }
		 
		 
		 void write_return(string funcname)
		 {       
		        
		        {
		 	    //cout<<"in return function"<<endl;
		 		outfile<<"// performing return operation .. "<<endl;
		 		outfile<<"@LCL"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@endframe"<<endl;
				outfile<<"M = D"<<endl;
				
				outfile<<"@5"<<endl;
			    outfile<<"D = A"<<endl;
			    outfile<<"@endframe"<<endl;
				outfile<<"A = M-D"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@retAddr"<<endl;
				outfile<<"M = D"<<endl;
				
				outfile<<"@SP"<<endl;
			    outfile<<"A = M-1"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@ARG"<<endl;
				outfile<<"A = M"<<endl;
				outfile<<"M = D"<<endl;
				
				outfile<<"@ARG"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@SP"<<endl;
				outfile<<"M = D+1"<<endl;
				
				outfile<<"@1"<<endl;
			    outfile<<"D = A"<<endl;
			    outfile<<"@endframe"<<endl;
				outfile<<"A = M-D"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@THAT"<<endl;
				outfile<<"M = D"<<endl;
				
				outfile<<"@2"<<endl;
			    outfile<<"D = A"<<endl;
			    outfile<<"@endframe"<<endl;
				outfile<<"A = M-D"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@THIS"<<endl;
				outfile<<"M = D"<<endl;
				
				outfile<<"@3"<<endl;
			    outfile<<"D = A"<<endl;
			    outfile<<"@endframe"<<endl;
				outfile<<"A = M-D"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@ARG"<<endl;
				outfile<<"M = D"<<endl;
				
				outfile<<"@4"<<endl;
			    outfile<<"D = A"<<endl;
			    outfile<<"@endframe"<<endl;
				outfile<<"A = M-D"<<endl;
				outfile<<"D = M"<<endl;
				outfile<<"@LCL"<<endl;
				outfile<<"M = D"<<endl;
				//if(myvar>1)
				{
				outfile<<"@retAddr"<<endl;	
				outfile<<"A = M"<<endl;
					//outfile<<"@"<<funcname<<"$return"<<endl;
				outfile<<"0;JMP"<<endl;
				}
			}
			
		 }
		
        void write_arith(string st)
         {
    	if(st == "add")
    	{
    	   outfile<<"// performing add operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = D+A"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"A  = M"<<endl;
		   outfile<<"M = D"<<endl;	
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M+1"<<endl;
		}
		
		if(st == "sub")
		{
			outfile<<"// performing subtraction operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = A-D"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"M = D"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M+1"<<endl;
		   	
		}
		if(st == "neg")
		{
			outfile<<"// performing nagate arithmetic operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"M = -D"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M+1"<<endl;
		}
		
        	}
	
	
	
	    void write_logical(string st)
          {
    	if(st == "eq")
		{
			outfile<<"// checking if equal  i.e  eq operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = D-A"<<endl;
		   outfile<<"@put_1"<<loop<<endl;
		   outfile<<"D;JEQ"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"M =  0"<<endl;	
       	   outfile<<"@eq_complete"<<loop<<endl;
           outfile<<"0;JMP"<<endl;
		   outfile<<"(put_1"<<loop<<")"<<endl;	
		   outfile<<"@SP"<<endl;	
		   outfile<<"A = M"<<endl;	
		   outfile<<"M = -1"<<endl;	 
           outfile<<"(eq_complete"<<loop<<")"<<endl;
           outfile<<"@SP"<<endl;
           outfile<<"M = M+1"<<endl;
           loop++;
		}
		
		
		if(st == "lt")
		{
			outfile<<"// checking if less than  i.e lt operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = A-D"<<endl;
		   outfile<<"@put_1"<<loop<<endl;
		   outfile<<"D;JLT"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"M =  0"<<endl;	
       	   outfile<<"@lt_complete"<<loop<<endl;
           outfile<<"0;JMP"<<endl;
		   outfile<<"(put_1"<<loop<<")"<<endl;	
		   outfile<<"@SP"<<endl;	
		   outfile<<"A = M"<<endl;	
		   outfile<<"M = -1"<<endl;	 
           outfile<<"(lt_complete"<<loop<<")"<<endl;
           outfile<<"@SP"<<endl;
           outfile<<"M = M+1"<<endl;
           loop++;
		}
		
    	if(st == "gt")
		{
			outfile<<"// checking if greater than  i.e gt operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = A-D"<<endl;
		   outfile<<"@put_1"<<loop<<endl;
		   outfile<<"D;JGT"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"M =  0"<<endl;	
       	   outfile<<"@gt_complete"<<loop<<endl;
           outfile<<"0;JMP"<<endl;
		   outfile<<"(put_1"<<loop<<")"<<endl;	
		   outfile<<"@SP"<<endl;	
		   outfile<<"A = M"<<endl;	
		   outfile<<"M = -1"<<endl;	 
           outfile<<"(gt_complete"<<loop<<")"<<endl;
           outfile<<"@SP"<<endl;
           outfile<<"M = M+1"<<endl;
           loop++;
		}
		
		
		if(st == "and")
		{
			outfile<<"// performing and operation  i.e and operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = D&A"<<endl;
		   
		   outfile<<"@SP"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"M = D"<<endl;
		   
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M+1"<<endl;
		  
		}
		
		if(st == "or")
		{
			outfile<<"// performing or operation  i.e or operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = D|A"<<endl;
		   
		    outfile<<"@SP"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"M = D"<<endl;
		   
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M+1"<<endl;
		   
		   
          
		}
		
		if(st == "not")
		{
			outfile<<"// performing not operation  i.e not operation .. "<<endl;
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M-1"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"D = M"<<endl;
		   outfile<<"D = !D"<<endl;
		   
		    outfile<<"@SP"<<endl;
		   outfile<<"A = M"<<endl;
		   outfile<<"M = D"<<endl;
		   
		   outfile<<"@SP"<<endl;
		   outfile<<"M = M+1"<<endl;
		   
		}
		
		
	       }
	       
	       
	       void write_pushpop(string st1, string st2, string mynum)
	           {  
	                
	                
  				 	int numtemp[20];
  				 	int num = 0;
	           		int ml =1;
	           		 int m = 0;  				
  				 	for(int k =0; k<mynum.size(); k++)
  				 	 {  
						 if(mynum[k]!=' ' && mynum[k]!='	')
    					 {
    					  numtemp[m] = mynum[k]-48;
    					  m++;
						  }
						}
					
    				for(int k =(m-1); k>=0; k--)
    				{ 
					   num = num+ numtemp[k]*ml;
    				   ml = ml* 10;
					}
					//cout<<"string is  = "<<mynum+"its"<<endl;
					//cout<<"num = "<<num<<endl;
					if(st1 == "pop")
				{
					
					if(st2 == "local")
				    {
				    	outfile<<"//code for pop local "<<num<<endl;
				    	outfile<<"@"<<num<<endl;
				    	outfile<<"D = A"<<endl;
				    	outfile<<"@LCL"<<endl;
				    	outfile<<"AD = D+M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M - 1"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	
				    	
					}
					
					 if(st2 == "argument")
				    {
				    		outfile<<"//code for pop argumnent "<<num<<endl;
				    	outfile<<"@"<<num<<endl;
				    	outfile<<"D = A"<<endl;
				    	outfile<<"@ARG"<<endl;
				    	outfile<<"AD = D+M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M - 1"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
					}
					
					 if(st2 == "this")
				    {
				    		outfile<<"//code for pop THIS "<<num<<endl;
				    	outfile<<"@"<<num<<endl;
				    	outfile<<"D = A"<<endl;
				    	outfile<<"@THIS"<<endl;
				    	outfile<<"AD = D+M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M - 1"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
					}
					
					 if(st2 == "that")
				    {
				    		outfile<<"//code for pop THAT "<<num<<endl;
				    	outfile<<"@"<<num<<endl;
				    	outfile<<"D = A"<<endl;
				    	outfile<<"@THAT"<<endl;
				    	outfile<<"AD = D+M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M - 1"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
					}
					
					 if(st2 == "static")
				    {
				        outfile<<"//code for pop STATIC "<<num<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M - 1"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@"<<stemp<<"."<<num<<endl;
				    	outfile<<"M = D"<<endl;
					}
					
					 if(st2 == "pointer")
				    {
				    	outfile<<"//code for pop POINTER "<<num<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M - 1"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	if(num == 0)
                           	 outfile<<"@THIS"<<endl;
				     	else if(num == 1)
					         outfile<<"@THAT"<<endl;
				    	
				    	outfile<<"M = D"<<endl;
					} 
					
					if(st2 == "temp")
				    {
				    	outfile<<"//code for pop TEMP "<<num<<endl;  
				    	outfile<<"@"<<num<<endl;
				    	outfile<<"D = A"<<endl;
				    	outfile<<"@5"<<endl;
				    	outfile<<"AD = D+A"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M - 1"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@var"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
					}
				   
				}
				
				
				
	           else	if(st1 == "push")
	           	{ 
				  
				    if(st2 == "local")
				    {  
					    outfile<<"//code for push local "<<num<<endl;
					    outfile<<"@"<<num<<endl;
					    outfile<<"D = A"<<endl;
				    	outfile<<"@LCL"<<endl;
				    	outfile<<"A = D+M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
					}
					
					 if(st2 == "argument")
				    {
				    	 outfile<<"//code for push argument "<<num<<endl;
				    	 outfile<<"@"<<num<<endl;
					    outfile<<"D = A"<<endl;
				    	outfile<<"@ARG"<<endl;
				    	outfile<<"A = D+M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
					}
					
					 if(st2 == "this")
				    {
				    	 outfile<<"//code for push THIS "<<num<<endl;
				    	 outfile<<"@"<<num<<endl;
					    outfile<<"D = A"<<endl;
				    	outfile<<"@THIS"<<endl;
				    	outfile<<"A = D+M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
					}
					
					 if(st2 == "that")
				    {
				    	 outfile<<"//code for push THAT "<<num<<endl;
				    	 outfile<<"@"<<num<<endl;
					    outfile<<"D = A"<<endl;
				    	outfile<<"@THAT"<<endl;
				    	outfile<<"A = D+M"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
				    	
					}
					
					 if(st2 == "constant")
				    { 
				    	 outfile<<"//code for push CONSTANT "<<num<<endl;
				    	outfile<<"@"<<num<<endl;
				    	outfile<<"D = A"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
					}
										
					 if(st2 == "static")
				    {
				    	 outfile<<"//code for push STATIC "<<num<<endl;
				    	outfile<<"@"<<stemp<<"."<<num<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
					}
					
					 if(st2 == "pointer")
				    {     outfile<<"//code for push pointer "<<num<<endl;
				    	if(num == 0)
                           	 outfile<<"@THIS"<<endl;
				     	else if(num == 1)
					         outfile<<"@THAT"<<endl;
					
					    
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
				    	
					} 
					
					if(st2 == "temp")
				    {
				    	outfile<<"//code for push temp "<<num<<endl;
				    	outfile<<"@"<<num<<endl;
					    outfile<<"D = A"<<endl;
				    	outfile<<"@5"<<endl;
				    	outfile<<"A = D+A"<<endl;
				    	outfile<<"D = M"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"A = M"<<endl;
				    	outfile<<"M = D"<<endl;
				    	outfile<<"@SP"<<endl;
				    	outfile<<"M = M+1"<<endl;
					}
				   
				   
				}
				
				
				
				
			   }
			   
		void endline()
		{
			outfile<<"//code for end loop "<<endl;
			outfile<<"(endloop)"<<endl;
					    outfile<<"@endloop"<<endl;
				    	outfile<<"0;JMP"<<endl;
				    	closefile();
			
			   }	   
			   
		void closefile()
		{ outfile.close();
		}
	
};

int codeWriter::loop = 0;
int codeWriter::myvar = 0;//initially 0
int codeWriter::bootvar = 0;


class parser: public codeWriter
{
  ifstream myfile;
  char line[100];
  char command[20];
  string com1;
  string com2; 
  string com3;
  string retfun;
  
public:
	parser(char *arg[],string outname,string stemp):codeWriter(outname,stemp)
           {  
		    myfile.open((*arg));
        }
        
        parser(string f_name, string outname, string stemp):codeWriter(outname,stemp,1)
        {  
        
        	int n = f_name.length();
		    char ch_array[n+1];
		    strcpy(ch_array,f_name.c_str());
		    myfile.open(ch_array);
		}

    bool hasmoreCommands()
    {   
    	return !(myfile.eof());
	}
    void advance()
    {
    	
          
      if(hasmoreCommands())
      {  
	     int i = 0;
         myfile.getline(line,100);
         string ss = line;
         
         
		while(line[i]!='\0')
	    {   // below if ignores comments from the vm file.
	        if(line[i] == '/'  && line[i+1] == '/')
	             { line[i] = '\0';
		           break;
	             } 
	             i++;
			}
				ss = ss.substr(0,i);
				 {
              
                 {
                 	int pos1 = ss.find(" ");
	                 com1 = ss.substr(0,pos1);					
                 }
               
                  {   
                  
                     int pos1 = ss.find(" ");
	                 string sub = ss.substr(pos1 + 1);
	                 int pos2 = sub.find(" ");
	                 com2 = sub.substr(0,pos2);	              			                 
                 }
                 
                  {
				     int pos1 = ss.find(" ");
	                 string sub = ss.substr(pos1 + 1);
	                 int pos2 = sub.find(" ");
	                 sub = sub.substr(pos2+1); 
	                 int pos3 = sub.find(" ");
	                 com3 = sub.substr(0,pos3);    
					            
                 }
                 
             }	   

		if(com1 == "function")
		  retfun = com2;
		else
		  retfun = retfun;
	    int type = command_type(com1);
	    
		if(type == 1)
		    write_pushpop(com1,com2,com3);
		else if(type == 2)
		     write_arith(com1);
	    else if(type == 3)
	          write_logical(com1);
	    else if(type == 4)
	          write_goto(com2);
	    else if(type == 5)
	          write_ifgoto(com2);
	    else if(type == 6)
	          write_label(com2);
	    else if(type == 7)
	          write_call(com2,com3);
	    else if(type == 8)
	          write_function(com2,com3);
	    else if(type == 9)
	          write_return(retfun);
	    else if(type == 0){}

		
    }
     if(hasmoreCommands())
      {advance();
	  return;}
      else
        {
        	inclose();
        	//endline();
        	closefile();
     	    return;
		}
}


    int	command_type(string c)
         {
         	if(c == "push" || c == "pop")
         	  return 1;
         	else if(c == "add" || c == "sub" || c == "neg")
         	  return 2;
         	else if(c == "eq" || c == "lt" || c == "gt" || c == "and" || c == "or" || c == "not")
               return 3;
            else if(c == "goto")
               return 4;
            else if(c == "if-goto")
               return 5;
            else if(c == "label")
               return 6;
            else if(c == "call")
               return 7;
            else if(c == "function")
               return 8;
            else if(c == "return")
               return 9;
            else
               return 0;
		 }
   
    void inclose(){
    	myfile.close();
	}    

};


  
int main(int argc, char *argv[1])
{
	//cout<<argv[1][0];
	string starg = argv[1];
	char ctemp[30];
	int len = starg.length();
	if(starg[len-3]=='.'&&starg[len-2]=='v'&&starg[len-1]=='m')
	{
	               int pos = starg.find(".");
                    string stemp = starg.substr(0,pos);
   					string outname = stemp+".asm";
parser p(argv+1,outname,stemp);
p.advance();
return 0;}
else
{   
	string ss = argv[1];
	string foldername = ss;
	string direct;
	//cout<<ss;
	int pos = 0;
	while(pos!= -1)
	{
		pos = foldername.find("/");// otherwise use foldername.find(92)  for forward slash. here 92 is the ASCII for forward slash.
		foldername = foldername.substr(pos+1);
		direct = ss.substr(0,pos);
	}

    DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir(argv[1]) ){
                while(entry = readdir(pDIR)){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                        {   string s = entry->d_name;// its the file name with .vm extension.
                            int len = s.length();
                            int pos = s.find(".");
                            string sub = s.substr(pos+1);
                            if(sub == "vm")
                            {   string outfile = direct+"/"+foldername+".asm";
                                string inpfile = direct+"/"+s;
                                 
                                string stemp = s.substr(0,pos);// its the file name without .vm extension.
                            	parser *p = new parser(inpfile,outfile,stemp);
                            	p->advance(); 
							}
                        	
						}
						
                        
                }
                closedir(pDIR);
        }
        
        return 0;
}
//p.write_boot();
//The above function should be called only when the argumrnt is a directory 

}

/*

#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include<dirent.h>
using namespace std;



int main(int argc, char *argv[1]){
	string ss = argv[1];
	cout<<ss;
    DIR *pDIR;
        struct dirent *entry;
        if( pDIR=opendir(argv[1]) ){
                while(entry = readdir(pDIR)){
                        if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
                        cout << entry->d_name << "\n";
                }
                closedir(pDIR);
        }
    return 0;
}



*/

