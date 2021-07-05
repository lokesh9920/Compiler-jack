#include<bits/stdc++.h>
#include <fstream>
#include<string.h>
#include<dirent.h>

using namespace std;



class jackTokenizer
{
  ifstream myfile;
  ofstream oufile;
  char line[100];
  char command[20];
  string com1;
  string com2; 
  string com3;
  string retfun;
  bool flag = 0;
  int flg = 0;
  
  
public:
        jackTokenizer(string f_name, string outname)
        {  
        
        	int n = f_name.length();
        	int m = outname.length();
		    char ch_array[n+1];
		    char ch_array_out[m+1];
		    strcpy(ch_array,f_name.c_str());
		    strcpy(ch_array_out,outname.c_str());
		    myfile.open(ch_array);
		    oufile.open(ch_array_out);
		    oufile<<"<tokens>"<<endl;
		}	

    bool hasmoreCommands()
    {   
    	return !(myfile.eof());
	}
	
	
    void advance()
    {int pos1 = 0;
     
          
      if(hasmoreCommands())
      {  
      label:
	     int i = 0;
         myfile.getline(line,100);
         string ss = line;
         string teep;
         
         
		while(line[i]!='\0')
	    {   // below if ignores comments from the vm file.
	        if(line[i] == '/'  && (line[i+1] == '/' || line[i+1] == '*'))
	             { line[i] = '\0';
	               if(line[i+1] == '*')
	               {
	               	flg = 1;
	               	int j = i+1;
	               	while(line[j]!='\0')
	               	{if((line[j] == '*'  && line[j+1] == '/'))
	                      {   flg = 0;
	                      goto label;
	             	
				                }
								j++;
					   }
				   }
		           break;
		        
	             } 
	             if((line[i] == '*'  && line[i+1] == '/'))
	             {   flg = 0;
	             goto label;
	             	
				 }
	                 
	             i++;
			}
			//cout<<flg<<endl;
			if(flg == 0){
				ss = ss.substr(0,i);
				for(int i = 0;i<ss.length();i++)
				{
					if(ss[i] == ' '|| ss[i] == '	')
					continue;
					else
					 {ss = ss.substr(i);
					 break;
					 }
				}
				
				string mysub = ss;
				//cout<<mysub<<endl;
				int quotepos = mysub.find("\"");
				string qt;
				int quotepos2;
				if(quotepos!=-1){
					qt = mysub.substr(quotepos+1);
				    quotepos2 = qt.find("\"");
				qt = qt.substr(0,quotepos2);
				}
				
				//cout<<"quotepos = "<<quotepos<<endl;
				//cout<<"qt is = "<<qt<<endl;
				while(1){
				int pre = 0;
				int count = 0;
				int pos = mysub.find(" ");
				com1 = mysub.substr(0,pos);
					//cout<<com1<<endl;
				for(int i = 0;i<com1.length();)
				{
					string stp(1,com1[i]);
					//cout<<stp<<endl;
					//cout<<is_Symbol(stp)<<endl;
					
					
					if(stp == "\"")
					{if(qt!="" && flag == 0)
					{
						oufile<<"<stringConstant"<<"> "<<qt<<" </stringConstant"<<">"<<endl;
						}
						flag = !flag;
						
						pre = i+1;
				        	
					}
					
					if(flag == 0)
					{
					if(is_Symbol(stp))
				     {  
					    string fnl = token_type(com1.substr(pre,count));
				        //cout<<"com1.substr = "<<com1.substr(pre,count)<<endl;
				        //cout<<"fnl is = "<<fnl<<endl;
				        if(fnl!="none"&& fnl!="symbol")
                            oufile<<"<"<<fnl<<"> "<<com1.substr(pre,count)<<" </"<<fnl<<">"<<endl;
                            if(stp == "<"){stp = "&lt;";
							}
							if(stp == ">"){stp = "&gt;";
							}
							if(stp == "&"){stp = "&amp;";
							}
				        oufile<<"<symbol> "<<stp<<" </symbol>"<<endl;	
				        pre = i+1;
				        count = 0;
				        
				      			     	
				       }
				    else if(i == (com1.length()-1))
				       {  string fnl = token_type(com1.substr(pre,count+1));
				       	 //cout<<"com1.substr = "<<com1.substr(pre,count+1)<<endl;
				       	 //cout<<"fnl is = "<<fnl<<endl;
				       	 if(fnl!="none")
                            oufile<<"<"<<fnl<<"> "<<com1.substr(pre,count+1)<<" </"<<fnl<<">"<<endl;
					   }
				     else
				     {
				     	count++;
					 }
					 }
					 i++;
				}
				mysub = mysub.substr(pos+1);
				if(mysub == ""||pos == -1)
				 break;
				}
			}
				
			
				
              
            
     if(hasmoreCommands())
      {advance();
	  return;}
      else
        {    oufile<<"</tokens>"<<endl;
        	Tclose();
     	    return;
		}
}
}


   string token_type(string c)
         { if(c!="" &&c!=" "&&c!="	")
		 {
         	if(is_keyword(c))
         	  return "keyword";
         	
         	else if(is_Symbol(c))
               return "symbol";
               
            else if(is_Number(c))
         	  return "integerConstant";
         	  
            else
               return "identifier";
		   }
		
		else
		return "none";
		 }
   
    int is_keyword(string s)
    {
    	
    	if(s == "class"|| s == "constructor"|| s ==  "function"|| s == "method"|| s == "static"|| s == "field"|| s == "var"|| s == "int"|| s == "char"|| s == "boolean"|| s == "void"|| s == "true")
                  return 1;
        else if(s == "false"|| s == "null"|| s == "this"|| s == "let"|| s == "do"|| s == "if"|| s == "else"|| s == "while"|| s == "return")
                  return 1;
        else
           return 0;
	}
   
   bool is_Symbol(string s)
   {
   	if( s == "(" || s == ")" || s == "{" || s == "}" || s == "[" || s == "]" || s == "." )
	    return true; 
	 else if( s == "," || s == ";" || s == "+" ||  s == "-" || s == "*" || s == "/" || s == "&"||  s == "|"|| s == "<"||  s == ">"||  s == "="||  s == "~")
   	  return true;
    else 
	return false; 
   }
   
   int is_Number(string s)
   {   	for (int i = 0; i < s.length(); i++)
		{if (int(s[i]) > 47 && int(s[i]) < 58)
			continue;
		else
		   return 0;
		}

	return 1;
    }
   
    void Tclose(){
    	myfile.close();
    	oufile.close();
	}    

};



class compilationEngine{
	// checks the syntax of the jack code.s
	string token;
	string tokentype;
	char line[100];
	string linestring;	
	ifstream ifile;
	ofstream ofile;
	public:
		compilationEngine(string f_name, string outname)
        {  
        
        	int n = f_name.length();
        	int m = outname.length();
		    char ch_array[n+1];
		    char ch_array_out[m+1];
		    strcpy(ch_array,f_name.c_str());
		    strcpy(ch_array_out,outname.c_str());
		    ifile.open(ch_array);
		    ofile.open(ch_array_out);
		    
		    tokenAdvance();
		    tokenAdvance();
		    compileClass();
		}
		
		
		void tokenAdvance(){
			ifile.getline(line,100);
			linestring = line;
			int pos = linestring.find("<");
			int pos1 = linestring.find(">");
			if(pos1!=linestring.length()-1)
			{
				string sub = linestring.substr(pos1+2);
				tokentype = linestring.substr(pos+1,pos1-pos-1);
			pos1 = sub.find(" ");
			token = sub.substr(0,pos1);
			//cout<<token<<endl;
			//cout<<tokentype<<endl;
			}
		}
		void eat(string s,int i = 0){
			int flag = 0;
			if(token == s){
				ofile<<linestring<<endl;
				flag = 1;
			}
			if(i == 0||flag == 1)
			   tokenAdvance();
		}
		void eattype(string s,int i = 0){
			int flag = 0;
			if(tokentype == s){
				ofile<<linestring<<endl;
			 flag = 1;
			}
			if(i == 0||flag == 1)
			  tokenAdvance();
		}
		
		void compileClass(){
			ofile<<"<class>"<<endl;
			eat("class");
			eattype("identifier");
			eat("{");
			do{
				compileclassvardec();
			}while(token == "field"|| token == "static");
			
			do{
			    compilesubroutinedec();
			}while(token == "function"|| token == "method"||token == "constructor");
			eat("}");
			ofile<<"</class>"<<endl;
			
		}
		///////////////////////////////below class tested ok.///////////////////////////////
		void compileclassvardec(){
			if(token == "field"|| token == "static"){
				ofile<<"<classVarDec>"<<endl;
			if(token == "field"|| token == "static")
		      	ofile<<linestring<<endl;
		    tokenAdvance();
		    //if(token == "int"|| token == "char"|| token == "boolean")
		      	ofile<<linestring<<endl;
		    tokenAdvance();
		    eattype("identifier");
		    do{
		    	eat(",",1);
		    eattype("identifier",1);
			}while(token!= ";");
			eat(";");
		    ofile<<"</classVarDec>"<<endl;
			}
			
			
		}
		
		void compilesubroutinedec(){
			ofile<<"<subroutineDec>"<<endl;
			//cout<<"enterd sub dec"<<endl;
			if(token == "function"|| token == "method"||token == "constructor"){
				ofile<<linestring<<endl;
				//cout<<"its function"<<endl;
			}
		      	
            string prev = token;
            
		    tokenAdvance();
			if(prev != "constructor"){
			
			  if(token == "int"|| token == "char"|| token == "boolean"||token == "void"){
			  	ofile<<linestring<<endl;
		      	 tokenAdvance();
			  }
			  } 	 
		    else
		       eattype("identifier");
		    
		    eattype("identifier");
		    eat("(");
		    compileparameterlist();
		    eat(")");
		    
		     compilesubroutinebody();
		    
			 ofile<<"</subroutineDec>"<<endl;
			//cout<<"dec completed"<<endl;
		}
		
		
		///////////////////////////////below class tested ok.///////////////////////////////
		void compileparameterlist(){
			ofile<<"<parameterList>"<<endl;
			do{
				eattype("keyword",1);
				eattype("identifier",1);
				eat(",",1);				
			}while(token!=")");
			ofile<<"</parameterList>"<<endl;
		}
		
		void compilesubroutinebody(){
			//cout<<"sub rot body entered"<<endl;
			ofile<<"<subroutineBody>"<<endl;
			eat("{");
			do{
				compilevardec();
			}while(token == "var");
			
			compilestatements();
			
			eat("}");
			ofile<<"</subroutineBody>"<<endl;
		}
		
		void compilevardec(){
			
			
			if(token == "var"){
				ofile<<"<varDec>"<<endl;
		      	ofile<<linestring<<endl;
		    tokenAdvance();
		    
		      	ofile<<linestring<<endl;
		    tokenAdvance();
		    eattype("identifier");
		    do{
		    	eat(",",1);
		    eattype("identifier",1);
			}while(token!= ";");
			eat(";");
			ofile<<"</varDec>"<<endl;
			}
		    
			
		}
		void compilestatements(){
			ofile<<"<statements>"<<endl;
			
			do{
				
				if(token == "let")
			   compilelet();
			   
			if(token == "do")
			   compiledo();
			if(token == "while")
			   compilewhile();
			if(token == "if")
			   compileif();
			if(token == "return")
			   compilereturn();
			   
			}while(token != "}");
             //cout<<"came out"<<endl;
			ofile<<"</statements>"<<endl;
		}
		
		void compilelet(){
			//cout<<"entered let statement"<<endl;
			ofile<<"<letStatement>"<<endl;
			eat("let");
			eattype("identifier");
			
			/////////////////////////////////
			
			if(token == "["){
				eat("[");
				compileexpression();
				eat("]");
			}
			eat("=");
			compileexpression();
			eat(";");
			//cout<<token<<endl;
			ofile<<"</letStatement>"<<endl;
			
		}
		void compiledo(){
			ofile<<"<doStatement>"<<endl;
			eat("do");
			//cout<<"entered do"<<endl;
			////////////////////////////////////////////////
			compilesubroutinecall();
			eat(";");
			//cout<<"done do"<<endl;
			ofile<<"</doStatement>"<<endl;
			
			
		}
		
		void compilewhile(){
			ofile<<"<whileStatement>"<<endl;
			eat("while");
			eat("(");
			compileexpression();
			eat(")");
			eat("{");
			compilestatements();
			eat("}");	 
			ofile<<"</whileStatement>"<<endl;
		}
		
		void compileif(){
			ofile<<"<ifStatement>"<<endl;
			eat("if");
			eat("(");
			compileexpression();
			eat(")");
			eat("{");
			compilestatements();
			eat("}");
			if(token == "else"){
				eat("else");
				eat("{");
				compilestatements();
				eat("}");
				
			}
			
			ofile<<"</ifStatement>"<<endl;
		}
		
		
		void compilereturn(){
		ofile<<"<returnStatement>"<<endl;
		//cout<<"return"<<endl;
		eat("return");
		if(token!= ";"){
			compileexpression();
		}
		eat(";");
		ofile<<"</returnStatement>"<<endl;	
		}
		
		void compileexpression(){
			ofile<<"<expression>"<<endl;
			//cout<<"entered expressions";
			if(token == "~"){
				compileterm();
			}
			else if(token == "-"){
				compileterm();
			}
			else
			 compileterm();
			//cout<<token<<endl;
			if(token == "+"||token == "&lt;"||token == "&gt;"||token == "-"||token == "="||token == "|"||token == "/"||token == "*"||token == "&amp;"){
				//cout<<token<<endl;
				
					eat(token);
				compileterm();
				
			}
			ofile<<"</expression>"<<endl;
		}
		void compileterm(){
			ofile<<"<term>"<<endl;
			 //cout<<"its term";
			 
			if(tokentype == "identifier"|| tokentype == "integerConstant"||tokentype == "stringConstant"||tokentype == "keyword"||token == "("){
				//ofile<<linestring<<endl;
				if(tokentype == "identifier"){
					eattype("identifier");
					//tokenAdvance();
					if(token == "["){
						eat("[");
						compileexpression();
						eat("]");
					}
					
				    else if(token == "."){
				         	eat(".");
				    		compilesubroutinecall();
					}
				}
				
				else if(token == "("){
						eat("(");
						compileexpression();
						//cout<<"main one"<<endl;
						eat(")");
					}
				else{
					ofile<<linestring<<endl;
					tokenAdvance();
				}
				
				
				
			}
			else if(token == "~"){
				eat(token);
				compileterm();
			}
			else if(token == "-"){
				eat(token);
				compileterm();
			}
			    
			//tokenAdvance();
			ofile<<"</term>"<<endl;
			return;
		}
		
		void compilesubroutinecall(){
			//cout<<"entered call "<<endl;
			eattype("identifier");
			if(token == "("){
				eat("(");
				compileexpressionlist();
				eat(")");
			} 
			else if(token == "."){
				eat(".");
				eattype("identifier");
				eat("(");
				compileexpressionlist();
				eat(")");
			
			}
			
		}
		void compileexpressionlist(){
			ofile<<"<expressionList>"<<endl;
			//cout<<"entered exp list"<<endl;
			if(token!=")"){
				compileexpression();
			do{//cout<<"itd do while"<<endl;
				if(token == ","){
				eat(",",1);
				compileexpression();
			      }
			}while(token!=")");
			}
			
			ofile<<"</expressionList>"<<endl;
			
		}
};





  
int main(int argc, char *argv[1])
{
	//cout<<argv[1][0];
	string starg = argv[1];
	char ctemp[30];
	int len = starg.length();
	if(starg[len-5]=='.'&&starg[len-4]=='j'&&starg[len-3]=='a'&&starg[len-2]=='c'&&starg[len-1]=='k')
	{   
	               int pos = starg.find(".");
                    string stemp = starg.substr(0,pos);
   					string outname = stemp+"T.xml";
   					string outfilefinal = stemp+".xml";
                     jackTokenizer p(starg,outname);
                            	p.advance();
                    //compilationEngine c(outname,outfilefinal);
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
                            if(sub == "jack")
                            {   string filenm = s.substr(0,pos);
							    string outfile = direct+"/"+filenm+"T.xml";
                                string inpfile = direct+"/"+s;
                                string outfilefinal = direct+"/"+filenm+".xml";
                                //cout<<outfilefinal<<endl;
                            	jackTokenizer *p = new jackTokenizer(inpfile,outfile);
                            	p->advance();
                            	compilationEngine *c = new compilationEngine(outfile,outfilefinal);
							}
                        	
						}
						
                        
                }
                closedir(pDIR);
        }
        
        return 0;
}
}

