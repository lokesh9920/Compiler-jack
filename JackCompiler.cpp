#include<bits/stdc++.h>
#include<cstdio>
#include <fstream>
#include<string.h>
#include<dirent.h>
#include<stack>
using namespace std;

string intorchar;
string fieldorvar;
string classorsub;
string classname;
string func_name;

struct Node{
	string name;
	string 	type;
	string kind;
	int index;
	Node* next;
};

class symbolTable{
	struct Node * classprev = NULL;
	struct Node* classhead = NULL;
	struct Node* subprev = NULL;
	struct Node* subhead = NULL;
	int varcount = 0,fieldcount = 0,argcount = 0,staticcount = 0;
	public:
		symbolTable(){
			//cout<<"default called";
			 fieldcount = 0;
			 staticcount = 0;
			 classhead = NULL;
			 classprev = NULL;		
		}
		
		void subroutineTable(){
			varcount = 0;
			argcount = 0;
			subhead = NULL;
			subprev = NULL;
		}
		
		
		
		void define(string nm,string typ,string knd){
			struct Node* temp = new Node();
			temp->name = nm;
			temp->type = typ;
			if(knd == "var")
			 temp->kind = "local";
			 else if(knd == "field")
			   temp->kind = "this";
			else			  
			temp->kind = knd;
			temp->index = variacount(knd);
			
			if(classorsub == "class"){
				classprev = classhead;
				temp->next = classprev;
				classhead = temp;
				
			}
			else{
				subprev = subhead;
				temp->next = subprev;
				subhead = temp;
			}
			//printTable();
		}
		
		int variacount(string knd){
			int temp;
			if(knd == "static"){
				
				temp = staticcount;
				staticcount+= 1;
				
				
			}
			else if(knd == "field"){
				
				temp = fieldcount;
				fieldcount+= 1;
				
			}
			else if(knd == "var"){
				
				temp = varcount;
				varcount+= 1;
			}
			
			else if(knd == "argument"){
				
				temp = argcount;
				argcount+= 1;
			}
			
			return temp;
		}
		
		string kindof(string s){
			struct Node* temp = subhead;
			while(temp!=NULL){
				if(temp->name == s){
					return temp->kind;
				}
				else{
					temp = temp->next;
				}
			}
			temp = classhead;
			while(classhead != NULL){
				if(temp->name == s){
					return temp->kind;
				}
				else{
					temp = temp->next;
				}
			}
			return "NONE";
		}
		
		
		
		
		string typeoof(string s){
			
			struct Node* temp = subhead;
			while(temp!=NULL){
				if(temp->name == s){
					return temp->type;
				}
				else{
					temp = temp->next;
				}
			}
			temp = classhead;
			while(classhead != NULL){
				if(temp->name == s){
					return temp->type;
				}
				else{
					temp = temp->next;
				}
			}
			return "NONE";
		}
		
		
		int getfieldcount(){
			return fieldcount;
		}
		
		
		int indexof(string s){
		       struct Node* temp = subhead;
			while(temp!=NULL){
				if(temp->name == s){
					return temp->index;
				}
				else{
					temp = temp->next;
				}
			}
			temp = classhead;
			while(classhead != NULL){
				if(temp->name == s){
					return temp->index;
				}
				else{
					temp = temp->next;
				}
			}
			return -1;
			
		}
		bool ispresent(string s){
			struct Node* temp = subhead;
			while(temp!=NULL){
				if(temp->name == s){
					return true;
				}
				else{
					temp = temp->next;
				}
			}
			//cout<<"creossed subhead"<<endl;
			temp = classhead;
			while(temp != NULL){
				if(temp->name == s){
					return 1;
				}
				else{
					temp = temp->next;
				}
			}
			return false;
		}
		
		
		/*
		void printTable(){
			struct Node* temp = subhead;
			if(temp == NULL)
			 //cout<<"sub is NULL."<<endl;
			while(temp!= NULL){
				
					cout<<temp->name<<"		";
					cout<<temp->type<<"		";
					cout<<temp->kind<<"		";
					cout<<temp->index<<endl;
			
					temp = temp->next;
				
			}
			
			
			temp = classhead;
			
			cout<<endl;
			cout<<endl;
			
			while(temp!= NULL){
				//cout<<"entered the class print";
					cout<<temp->name<<"		";
					cout<<temp->type<<"		";
					cout<<temp->kind<<"		";
					cout<<temp->index<<endl;
			
					temp = temp->next;
				
			}
			
	}*/
	
};



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
  string delf;
  
  
public:
        jackTokenizer(string f_name, string outname)
        {  
        
        	int n = f_name.length();
        	int m = outname.length();
		    char ch_array[n+1];
		    char ch_array_out[m+1];
		    delf = outname;
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

class vmWriter{
	ofstream vmfile;
	public:
		
		vmWriter(string vmname){
			//cout<<"required called";
			int n = vmname.length();
		    char ch_array[n+1];
		    strcpy(ch_array,vmname.c_str());
		    vmfile.open(ch_array);
		    
		}
		
		
		void writePush(string seg, int index){
			vmfile<<"push "<<seg<<" "<<index<<endl;
		}
		
		void writePop(string seg, int index){
			vmfile<<"pop "<<seg<<" "<<index<<endl;
		}
		
		void writeArithmetic(string com){
			vmfile<<com<<endl;
		}
		
		void writeLabel(int l_name){
			vmfile<<"label L"<<l_name<<endl;
		}
		
		void writeGoto(int l_name){
			vmfile<<"goto L"<<l_name<<endl;
		}
		
		void writeIf(int com){
			vmfile<<"if-goto L"<<com<<endl;
		}
		
		void writeCall(string fun,int nargs){
			vmfile<<"call "<<fun<<" "<<nargs<<endl;
		}
		
		void writeFunction(string f_name,int nlocals){
			vmfile<<"function "<<f_name<<" "<<nlocals<<endl;
			
		}
		void writeop(char c){
			//cout<<"writing op for: "<<c<<endl;
			if(c == '+')
			    vmfile<<"add"<<endl;
			else if(c == '-')
			     vmfile<<"sub"<<endl;
			else if(c == '<')
			   vmfile<<"lt"<<endl;
			else if(c == '>')
			   vmfile<<"gt"<<endl;
			else if(c == '=')
			   vmfile<<"eq"<<endl;
			else if(c == '&')
			   vmfile<<"and"<<endl;
			else if(c == '|')
			   vmfile<<"or"<<endl;
			else if(c == '*')
			   vmfile<<"call Math.multiply 2"<<endl;
			else if(c == '/')
			   vmfile<<"call Math.divide 2"<<endl;
		}
		void writeunary(char c,int a = 0){
			if(c == '-'){
				if(a == 1)
				   vmfile<<"sub"<<endl;
				else
				 vmfile<<"neg"<<endl;
				
			}
			  
			else if(c == '~')
			   vmfile<<"not"<<endl;
		}
	    void writeConstructor(int a){
		writePush("constant",a);
		writeCall("Memory.alloc",1);
		writePop("pointer",0);
		}
		
		void writeReturn(){
			vmfile<<"return"<<endl;
		}
		
		void vmclose(){
			vmfile.close();
		}
		
};

class compilationEngine:public symbolTable,public vmWriter
{
	// checks the syntax of the jack code.s
	string token;
	string tokentype;
	char line[100];
	int local_vars = 0;
	string linestring;	
	ifstream ifile;
	ofstream ofile;
	string fexp,fprev;
	int callargs = 0;
	string call_name;
	int glabelcount = 0;
	int glcount = 0;
	public:
		
		compilationEngine(string f_name, string outname,string vmname):vmWriter(vmname)
        {  
        
        	int n = f_name.length();
        	int m = outname.length();
		    char ch_array[n+1];
		    char ch_array_out[m+1];
		    strcpy(ch_array,f_name.c_str());
		    strcpy(ch_array_out,outname.c_str());
		    ifile.open(ch_array);
		    //ofile.open(ch_array_out);
		    
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
		void eat(string s,int i = 0,int nw = 0){
			int flag = 0;
			if(token == s){
				//ofile<<linestring<<endl;
				flag = 1;
				if(nw = 1){
					string stt = token;
					if(stt == "&lt;")
					   stt = "<";
					else if(stt == "&gt;")
					   stt = ">";
				    else if(stt == "&amp;")
				       stt = "&";
					fexp = fexp + stt;
				}
			}
			if(i == 0||flag == 1)
			   tokenAdvance();
		}
		void eattype(string s,int i = 0,int nw  = 0){
			int flag = 0;
			if(tokentype == s){
				ofile<<linestring<<endl;
			 flag = 1;
			 if(nw = 1){
					fexp = fexp + token;
				}
			}
			if(i == 0||flag == 1)
			  tokenAdvance();
		}
		
		void compileClass(){
			//ofile<<"<class>"<<endl;
			eat("class");
			classorsub = "class";
			classname = token;
			//cout<<"class name is : "<<classname<<endl;
			eattype("identifier");
			
			eat("{");
			do{
				compileclassvardec();
			}while(token == "field"|| token == "static");
			
			do{
			    compilesubroutinedec();
			}while(token == "function"|| token == "method"||token == "constructor");
			eat("}");
			//ofile<<"</class>"<<endl;
			
		}
		
		
		
		void compileclassvardec(){
			if(token == "field"|| token == "static"){
				//ofile<<"<classVarDec>"<<endl;
				fieldorvar = token;
			if(token == "field"|| token == "static")
		      	//ofile<<linestring<<endl;
		    tokenAdvance();
		    //if(token == "int"|| token == "char"|| token == "boolean")
		      	//ofile<<linestring<<endl;
		      	intorchar = token;
		    tokenAdvance();
		    define(token,intorchar,fieldorvar);
		    eattype("identifier");
		    
		    
		    do{
		    	eat(",",1);
		    	if(token!= ";")
		    	define(token,intorchar,fieldorvar);
		    eattype("identifier",1);
			}while(token!= ";");
			eat(";");
		    ofile<<"</classVarDec>"<<endl;
			}
			
			
		}
		
		void compilesubroutinedec(){
			//ofile<<"<subroutineDec>"<<endl;
			//cout<<"enterd sub dec"<<endl;
			if(token == "function"|| token == "method"||token == "constructor"){
				subroutineTable();
				//ofile<<linestring<<endl;
				classorsub = token;
				if(classorsub == "method"){
					define("this",classname,"argument");
				}
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
		    func_name = token;
		    //cout<<"func_name is : "<<func_name<<endl;
		    eattype("identifier");
		    eat("(");
		    compileparameterlist();
		    eat(")");
		    
		     compilesubroutinebody();
		    
			 //ofile<<"</subroutineDec>"<<endl;
			//cout<<"dec completed"<<endl;
		}
		
		
		///////////////////////////////below class tested ok.///////////////////////////////
		void compileparameterlist(){
			//ofile<<"<parameterList>"<<endl;
			fieldorvar = "argument";
			do{
			if(token != ")")
			   intorchar = token;
				eattype("keyword",1);
				eat("Array",1);
				if(token != ")")
				define(token,intorchar,fieldorvar);
				eattype("identifier",1);
				eat(",",1);				
			}while(token!=")");
			//ofile<<"</parameterList>"<<endl;
		}
		
		void compilesubroutinebody(){
			//cout<<"sub rot body entered"<<endl;
			//ofile<<"<subroutineBody>"<<endl;
			eat("{");
			
			do{
				compilevardec();
			}while(token == "var");
			writeFunction((classname+"."+func_name),local_vars);
			if(classorsub == "constructor" ){
				writeConstructor(getfieldcount());
			}
			else if(classorsub == "method"){
				writePush("argument",0);
				writePop("pointer",0);
			}
			//cout<<"localvars is : "<<local_vars<<endl;
			local_vars = 0;
			compilestatements();
			
			eat("}");
			//ofile<<"</subroutineBody>"<<endl;
		}
		
		void compilevardec(){
			
			
			if(token == "var"){
				fieldorvar = token;
				//ofile<<"<varDec>"<<endl;
		      	//ofile<<linestring<<endl;
		    tokenAdvance();
		       intorchar = token;
		      	//ofile<<linestring<<endl;
		    tokenAdvance();
		    define(token,intorchar,fieldorvar);
		    local_vars+=1;
		    eattype("identifier");
		    do{
		    	eat(",",1);
		    	if(token!= ";"){
		    		define(token,intorchar,fieldorvar);
		    		local_vars+=1;
				}
		    
		    eattype("identifier",1);
			}while(token!= ";");
			eat(";");
			//ofile<<"</varDec>"<<endl;
			}
		    
			
		}
		void compilestatements(){
			//ofile<<"<statements>"<<endl;
			
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
			//ofile<<"</statements>"<<endl;
		}
		
		void compilelet(){
			string ttoken;
			//cout<<"entered let statement"<<endl;
			//ofile<<"<letStatement>"<<endl;
			eat("let");
			string letvari = token;
			eattype("identifier");
			
			/////////////////////////////////
			ttoken = token;
			if(token == "["){			
				eat("[");
				fexp = "";
				writePush(kindof(letvari),indexof(letvari));
				compileexpression();
				//cout<<"expression is : "<<fexp<<endl;
				codeWrite(fexp);
			    fexp = "";
			    writeop('+');
				eat("]");
			}
			eat("=");
			fexp = "";
			compileexpression();
	        //cout<<"expression is : "<<fexp<<endl;
	        codeWrite(fexp);
			//codeWrite(fprev);
			    fexp = "";
			    fprev = "";
			    if(ttoken!="[")
			       writePop(kindof(letvari),indexof(letvari));
			
			else{
				writePop("temp",0);
            writePop("pointer",1);
			writePush("temp",0);
			writePop("that",0);		
			}
				
			
			eat(";");
			//cout<<token<<endl;
			//ofile<<"</letStatement>"<<endl;
			
		}
		void compiledo(){
			call_name = "";
			//ofile<<"<doStatement>"<<endl;
			eat("do");
			//cout<<"entered do"<<endl;
			////////////////////////////////////////////////
			fexp = "";
			compilesubroutinecall();
			//cout<<"expression in do is : "<<fexp<<endl;
			codeWrite(fexp);
			fexp = "";
			//vmfile<<callargs;
			//writeCall(call_name,callargs);
			callargs = 0;
			writePop("temp",0);
			eat(";");
			//cout<<"done do"<<endl;
			//ofile<<"</doStatement>"<<endl;
			
			
		}
		
		void compilewhile(){
			int labelcount;
			labelcount = glcount;
			//ofile<<"<whileStatement>"<<endl;
			labelcount+=2;
			eat("while");
			writeLabel(labelcount);
			glcount = labelcount;
			eat("(");
			fexp = "";
			compileexpression();
			//cout<<"expression is : "<<fexp<<endl;
			codeWrite(fexp);
			    fexp = "";
			    writeunary('~');			    
			eat(")");
			writeIf(labelcount+1); 
			eat("{");
			compilestatements();
			eat("}");	
			writeGoto(labelcount);
			writeLabel(labelcount+1); 
			//ofile<<"</whileStatement>"<<endl;
		}
		
		void compileif(){
			int labelcount;
			labelcount = glabelcount+5;
			//ofile<<"<ifStatement>"<<endl;
			eat("if");
			eat("(");
			fexp = "";
			compileexpression();
			//cout<<"expression is : "<<fexp<<endl;
			codeWrite(fexp);
			//writeunary('~');
			    fexp = "";
			eat(")");
			eat("{");
			writeIf(labelcount);
			glabelcount = labelcount;
			writeGoto(labelcount+1);
			writeLabel(labelcount);
			
			compilestatements();
			writeGoto(labelcount+1*1000);
			eat("}");
			writeLabel(labelcount+1);
			if(token == "else"){
				eat("else");
				eat("{");
				compilestatements();
				eat("}");
				
			}
			writeLabel(labelcount+1*1000);
			//ofile<<"</ifStatement>"<<endl;
		}
		
		
		void compilereturn(){
		//ofile<<"<returnStatement>"<<endl;
		//cout<<"return"<<endl;
		eat("return");
		if(token!= ";"){
			fexp = "";
			compileexpression();
			//cout<<"expression is : "<<fexp<<endl;
			codeWrite(fexp);
			    fexp = "";
		}
		else
		   writePush("constant",0);
		eat(";");
		
		writeReturn();
		//ofile<<"</returnStatement>"<<endl;	
		}
		
		void compileexpression(){
			//ofile<<"<expression>"<<endl;
			//cout<<"entered expressions";
			//fexp = "";
			if(token == "~"){
				compileterm();
				
			}
			else if(token == "-"){
				compileterm();
			}
			else{
				compileterm();
			}
			//cout<<token<<endl;
			if(token == "+"||token == "&lt;"||token == "&gt;"||token == "-"||token == "="||token == "|"||token == "/"||token == "*"||token == "&amp;"){
				//cout<<token<<endl;
					eat(token,0,1);
				compileterm();
				
			}
			
			//ofile<<"</expression>"<<endl;
		}
		void compileterm(){
			//ofile<<"<term>"<<endl;
			 //cout<<"its term";
			 
			if(tokentype == "identifier"|| tokentype == "integerConstant"||tokentype == "stringConstant"||tokentype == "keyword"||token == "("){
				////ofile<<linestring<<endl;
				if(tokentype == "identifier"){
					eattype("identifier",0,1);
					//tokenAdvance();
					if(token == "["){
						eat("[",0,1);
						compileexpression();
						eat("]",0,1);
					}
					
				    else if(token == "."){
				         	eat(".",0,1);
				    		compilesubroutinecall();
					}
				}
				
				else if(token == "("){
						eat("(",0,1);
						compileexpression();
						//cout<<"main one"<<endl;
						eat(")",0,1);
					}
				else{
					if(tokentype == "stringConstant"){
						int pos = linestring.find("<");
			int pos1 = linestring.find(">");
			if(pos1!=linestring.length()-1)
			{
				string sub = linestring.substr(pos1+2);
				
			pos1 = sub.find("<");
			string tp = sub.substr(0,pos1-1);
			fexp = fexp+"\""+tp+"\"";
					}
				}
					else {
							fexp = fexp+token;
					       // fprev = fexp;
					}
				
					//ofile<<linestring<<endl;
					tokenAdvance();
				}
				
				
				
			}
			else if(token == "~"){
				eat(token,0,1);
				compileterm();
			}
			else if(token == "-"){
				eat(token,0,1);
				compileterm();
			}
			    
			//tokenAdvance();
			//ofile<<"</term>"<<endl;
			return;
		}
		
		void compilesubroutinecall(){
			//cout<<"entered call "<<endl;
			//vmfile<<"call "<<token;
			call_name = call_name + token;
			eattype("identifier",0,1);
			if(token == "("){
				//vmfile<<" ";
				eat("(",0,1);
				compileexpressionlist();
				eat(")",0,1);
			} 
			else if(token == "."){
				call_name = call_name + token;
				//vmfile<<".";
				eat(".",0,1);
				call_name = call_name + token;
				//vmfile<<token;
				eattype("identifier",0,1);
				//vmfile<<" ";
				eat("(",0,1);	
				compileexpressionlist();
				eat(")",0,1);
			
			}
			
		}
		void compileexpressionlist(){
			//ofile<<"<expressionList>"<<endl;
			//cout<<"entered exp list"<<endl;
			//cout<<"fneeded is : "<<fexp<<endl;
			//fprev = fexp;
			if(token!=")"){
				//callargs+= 1;
				//fexp = "";
				compileexpression();
				//cout<<"expression is : "<<fexp<<endl;
				//codeWrite(fexp);
			    //fexp = "";
			do{//cout<<"its do while"<<endl;
				if(token == ","){
				//	callargs+= 1;
				eat(",",1,1);
				//fexp = "";
				compileexpression();
				//cout<<"expression is : "<<fexp<<endl;
				//codeWrite(fexp);
			    //fexp = "";
			      }
			}while(token!=")");
			}
			
			//ofile<<"</expressionList>"<<endl;
			
		}
		
		
		void codeWrite(string s,int aa = 0){
			string sbef;
			int opcount = 0;
			int clcount = 0;
			//cout<<"orig is : "<<s<<endl;
			if(s[0] == '(' &&  s[(s.length()-1)] == ')'){
				s.erase(0,1);
				s.erase((s.length()-1),1);
			}
			//cout<<"sss is : "<<s<<endl;
			
			
			if((s.find("(")!=-1 && s.find(")") == -1 ) ||  (s.find("(")==-1 && s.find(")") != -1)  )
			{
				if(s.find("(")!= -1){
					int psp = s.find("(");
					s.erase(psp,1);
				}
				else if(s.find(")")!= -1){
					int psp = s.find(")");
					s.erase(psp,1);
				}
				
			}
			
			if(s == "") return;
				//cout<<"sssssss is : "<<s<<endl;
			//cout<<"is present return value: "<<ispresent(s)<<endl;
			
			if(s == "null"){
				writePush("constant",0);
			}
			else if(s.find("\"")!= -1){
				string fstname = s.substr(0,s.find("("));
				string strinquote = s.substr(s.find("\"")+1);             
				strinquote = strinquote.substr(0,strinquote.find("\""));
				//cout<<"strinquote is : "<<strinquote<<endl;
                   writePush("constant",strinquote.length());
                   writeCall("String.new",1);
				for(int i = 0; i<strinquote.length();i++){
					writePush("constant",int(strinquote[i]));
					writeCall("String.appendChar",2);
				}
				writeCall(fstname,1);
				
			}
			//a[a[5]] * b[((7 - a[3]) - Main.double(2)) + 1]
			//else if((s.find("[")<s.find("(") && s.find("[")!=-1) && findop(s)>s.find("[") && findop(s)<s.find("]") && (!(istwoarrs(s))))
			else if((s.find("[")<s.find("(") && s.find("[")!=-1) ){
				//cout<<"entered oppos "<<endl;
				int  oppos = findop(s);
				if(oppos!=-1){
					string subb = s.substr(0,oppos);
				
				for(int i = 0; i<subb.length();i++){
					if(s[i] == '['){
						opcount+=1;
					}
					else if(s[i] == ']'){
						clcount+=1;
					}
				}
				if(opcount == clcount){
					codeWrite(subb);
					codeWrite(s.substr(oppos+1));
					writeop(s[oppos]);
				}
				else if(opcount == 1){
					s.erase((s.length()-1),1);
					string tarr = s.substr(0,s.find("["));
					writePush(kindof(tarr),indexof(tarr));
					codeWrite(s.substr(s.find("[")+1));
					writeop('+');
					writePop("pointer",1);
					writePush("that",0);
				}
				}
				else{
					s.erase((s.length()-1),1);
				string tarr = s.substr(0,s.find("["));
				writePush(kindof(tarr),indexof(tarr));
				codeWrite(s.substr(s.find("[")+1));
				writeop('+');
				writePop("pointer",1);
				writePush("that",0);
				}
				
				
				
				
				
			}
		
			else if(isnum(s)){
				//cout<<"entered isnum"<<endl;
				int numtemp[20];
  				 	int num = 0;
	           		int ml =1;
	           		 int m = 0;  				
  				 	for(int k =0; k<s.size(); k++)
  				 	 {  
						 if(s[k]!=' ' && s[k]!='	')
    					 {
    					  numtemp[m] =s[k]-48;
    					  m++;
						  }
						}
					
    				for(int k =(m-1); k>=0; k--)
    				{ 
					   num = num+ numtemp[k]*ml;
    				   ml = ml* 10;
					}
					writePush("constant",num);
					
			}
			
			
			else if(ispresent(s)){
				//cout<<"entered ispresent"<<endl;
				writePush(kindof(s),indexof(s));
			}
			
			else if(s[0] == '~'|| s[0] == '-'){
			//cout<<"entered unary check"<<endl;
			  codeWrite(s.substr(1));
			 writeunary(s[0],aa);
		}
		
			else if(hasop(s) && s.find(".") == -1 || findop(s)<s.find(".")){
				//cout<<"entered hasop"<<endl;
				
				if(s.find("(") == -1 || s[0]!='('){
					//cout<<"suspected place"<<endl;
					int pos;
					for(int i = 0;i<s.length();i++){
   							if(s[i] == '+'||s[i] == '<'||s[i]  == '>'||s[i]  == '-'||s[i] == '='||s[i]  == '|'||s[i]  == '/'||s[i]  == '*'||s[i]  == '&'){
   								pos = i;
   								break;}
				               }
				               //cout<<"the three parts are : "<<s.substr(0,pos)<<"    "<<s.substr(pos+1)<<"      "<<s[pos]<<endl;
			codeWrite(s.substr(0,pos));
			codeWrite(s.substr(pos+1));
			writeop(s[pos]);
					
				}
				
				else{
					string subs = s;
					string stng;
					
					while(1){
						
						//cout<<"subs in while is  : "<<subs<<endl;
							while(subs.find("(")<subs.find(")")   && subs.find("(")!=-1){
								if(subs.substr(0,subs.find("("))!="")
								 sbef = subs.substr(0,subs.find("("));
								//cout<<"sbef is : "<<sbef<<endl;
						subs = subs.substr((s.find("(")+1));
						
						
					}
					stng = subs.substr(0,subs.find(")"));
					codeWrite(stng,1);
				    
				    
					subs = subs.substr(subs.find(")")+1);
					//cout<<"subs is : "<<subs<<endl;
					
					if(subs.find(".")!=-1){
						string sbbs = subs.substr(subs.find(")")+1);
						//cout<<"sbbs is :"<<sbbs<<endl;
						int psps = subs.find(")");
						while(sbbs.find(")")!=-1){
							sbbs = sbbs.substr(sbbs.find(")")+1);
							psps = psps+sbbs.find(")")+1;
							
						}
						//cout<<"you are executing "<<subs.substr(0,psps+1)<<endl;
						codeWrite(subs.substr(0,psps+1),1);
						codeWrite(sbbs,1);
					    break;
						
					}
						if(subs.find(")")==-1){
							codeWrite(subs,1);
							break;
						}
						
						
					}
				codeWrite(sbef,1);
					
				}
		
		}
		
		
		
		else if(s == "this"){
			//cout<<"entered this "<<endl;
			writePush("pointer",0);
		}
		
		else if(s == "true" || s == "false"){
		//cout<<"entered truefalse"<<endl;
		 	if(s == "true"){
		 		writePush("constant",0);
		 		writeunary('~');
			 }
			 else
			 	writePush("constant",0);
		 }
		
		else if(s!=""){
			//cout<<"entered fcall"<<endl;
			if(s.find(".") == -1){
				writePush("pointer",0);
				callargs+=1;
				
			}
			int pos =  s.find("(");
			string sb = s.substr(pos+1);
			string fnm = s.substr(0,pos);			
			while(1){
				int ps = sb.find(",");
			if(ps!=-1){
				string b = sb.substr(0,ps);
				callargs+=1;
				codeWrite(b);
				sb = sb.substr(ps+1);
				
			}
			else{
				int pps = sb.find(")");
				sb = sb.substr(0,sb.length()-1);
				//cout<<"sb is "<<sb<<endl;
				if(sb!=""){
					callargs+=1;
				}
				  
				  
				codeWrite(sb);
				break;
			}
			
			}
			if(s.find(".") == -1){
				fnm = classname+"."+fnm;
			}
			else{
				
				if(ispresent(s.substr(0,s.find(".")))){
					fnm = typeoof(s.substr(0,s.find(".")))+"."+fnm.substr(fnm.find(".")+1);
					callargs+=1;
					writePush(kindof(s.substr(0,s.find("."))), indexof(s.substr(0,s.find("."))));
				}
			}
			writeCall(fnm,callargs);
			callargs = 0;
			
			
		}
		
		
		
		
	}


   int isnum(string s){
   	//cout<<" is in num"<<endl;
      	for (int i = 0; i < s.length(); i++)
		{if (int(s[i]) > 47 && int(s[i]) < 58)
			continue;
		else
		   return 0;
		}

	return 1;
    }
   
   
   bool hasop(string s){
   	for(int i = 0;i<s.length();i++){
   		if(s[i] == '+'||s[i] == '<'||s[i]  == '>'||s[i]  == '-'||s[i] == '='||s[i]  == '|'||s[i]  == '/'||s[i]  == '*'||s[i]  == '&'){
   			if(s.find(".")!=-1)
   			   return 0;
   			return 1;
		   }
	   }
	   return 0;
   }
   int findop(string s){
   	for(int i = 0;i<s.length();i++){
   		if(s[i] == '+'||s[i] == '<'||s[i]  == '>'||s[i]  == '-'||s[i] == '='||s[i]  == '|'||s[i]  == '/'||s[i]  == '*'||s[i]  == '&'){
   			
   			return i;
		   }
	   }
	   return -1;
   }
   
   bool istwoarrs(string s){
   		int pos = findop(s);
   	char c1,c2;
   	
   	for(int i = pos;i>0;i--){
   		if(s[i] == ' ')
   		   continue;
   		else{
   			c1 = s[i];
   		  break;
		   }   		
	   }
   
   	for(int i = pos;i<s.length();i++){
   		if(s[i] == ' ')
   		   continue;
   		else{
   			c2 = s[i];
   		  break;
		   }   		
	   }
	   	
	   if(c1 == ']'&& c2 == '['){
	   	return 1;
	   }
	   else
   	return 0;
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
   					string vmname  = stemp+".vm";
   					string outfilefinal = stemp+".xml";
                     jackTokenizer p(starg,outname);
                            	p.advance();
                    compilationEngine c(outname,outfilefinal,vmname);
                    //p.delfile();
                    //c.printTable();
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
							    string vmname  = direct+"/"+filenm+".vm";
                                string inpfile = direct+"/"+s;
                                string outfilefinal = direct+"/"+filenm+".xml";
                                //cout<<outfilefinal<<endl;
                            	jackTokenizer *p = new jackTokenizer(inpfile,outfile);
                            	p->advance();
                            	compilationEngine *c = new compilationEngine(outfile,outfilefinal,vmname);
                            	//p->delfile();
                            	//c->printTable();
							}
                        	
						}
						
                        
                }
                closedir(pDIR);
        }
        
        return 0;
}
}



