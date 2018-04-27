
#include <bits/stdc++.h>
#include <string>
#include <string.h>
using namespace std;

typedef struct table
{
        int row_count;
        int col_count;
       	string table_name;
        vector < string > column_names;
        vector< vector < int > > table_entry;
}table;

vector<table> Alltables;
int table_count=-1;

vector<string> query;
vector<int> non_repeat_index;
string lowercase(string word)
{
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        return word;
}

bool is_digits(const string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

string NumberToString(int num)
{
     std::ostringstream ss;
     ss << num;
     return ss.str();
}
  
vector<string> split(string input, char separator)
{
        string word="";
        vector<string> Allwords;
        int i=0;
        while(i<input.size())
        {
                if(input[i]!=separator)
                {
                        word =word+input[i];
                }
                else 
                {
                        Allwords.push_back(word);
                        word="";
                }
                i++;
        }
        Allwords.push_back(word);
        return Allwords;
}

int get_tableno(string tabname)
{
	for(int i=0;i<=table_count;i++)
   	{
   		if(Alltables[i].table_name.compare(tabname)==0)
   		{
   			return i;
   		}
   	}
   	return -1;
}

int get_colno_of_table(int tableno,string colname)
{
	for(int i=0;i<Alltables[tableno].col_count;i++)
   	{
   		if(Alltables[tableno].column_names[i].compare(colname)==0)
   		{
   			return i;  
   		}
   	}
   	return -1;
}
int get_colno(table temp_result,string colname)
{
	for(int i=0;i<temp_result.col_count;i++)
   	{
   		if(temp_result.column_names[i].compare(colname)==0)
   		{
   			return i;  
   		}
   	}
   	return -1;
}

string get_row_of_table(int tableno,int row_no)
{
	string tuple="";
	for(int i=0;i<Alltables[tableno].col_count;i++)
	{
		if(i!=Alltables[tableno].col_count-1)
		tuple+=NumberToString(Alltables[tableno].table_entry[row_no][i])+",";
		else
		tuple+=NumberToString(Alltables[tableno].table_entry[row_no][i]);
	}
	return tuple;
}
string get_row(table temp_result,int row_no)
{
	string tuple="";
	for(int i=0;i<temp_result.col_count;i++)
	{
		if(i!=temp_result.col_count-1)
		tuple+=NumberToString(temp_result.table_entry[row_no][i])+",";
		else
		tuple+=NumberToString(temp_result.table_entry[row_no][i]);
	}
	return tuple;
}

table cross_product(vector <string> tabs)
{
	table temp_result;
	for(int i=0;i<tabs.size();i++)
	{
		int tableno=get_tableno(tabs[i]);
		if(tableno==-1)
		{
			cout<<"ERROR::tablename:"<<tabs[i]<<" Does not exists"<<endl;
   			exit(0);
   		}
   	}
   	
   	//copy the contents of first table in temp_result
	int tableno=get_tableno(tabs[0]);
	temp_result=Alltables[tableno];
	for(int j=0;j<Alltables[tableno].col_count;j++)
	{
		temp_result.column_names[j]=Alltables[tableno].table_name+"."+Alltables[tableno].column_names[j];	
	}	
	
	vector < string > row_entry;
	string tab_row,temp_row,new_row;
	for(int i=1;i<tabs.size();i++)
	{		
		row_entry.clear();
		int tableno = get_tableno(tabs[i]);
		for(int j=0;j<temp_result.row_count;j++)
		{	
			temp_row=get_row(temp_result,j);
			new_row="";						
			for(int k=0;k<Alltables[tableno].row_count;k++)
			{
				tab_row=get_row_of_table(tableno,k);
				new_row=temp_row+","+tab_row;
			//	cout<<new_row<<endl;
				row_entry.push_back(new_row);
			}				
		}
		
		for(int j=0;j<Alltables[tableno].col_count;j++)
		{
			temp_result.column_names.push_back(Alltables[tableno].table_name+"."+Alltables[tableno].column_names[j]);	
			temp_result.col_count++;
		}	
		temp_result.table_entry.clear();		
		for(int j=0;j<row_entry.size();j++)
		{
			vector<string> tab_entry = split(row_entry[j],',');
       		vector<int> tabrow_entry;                
        	for(int k=0;k<tab_entry.size();k++)
        	{
        		tabrow_entry.push_back(atoi(tab_entry[k].c_str()));
        	}  
       		temp_result.table_entry.push_back(tabrow_entry);	
        }
        temp_result.row_count=row_entry.size();
	}
	return temp_result;
}

int col_max(int tableno,int colno)
{
	int max=Alltables[tableno].table_entry[0][colno];
	for(int i=1;i<Alltables[tableno].row_count;i++)
   	{
   		if(Alltables[tableno].table_entry[i][colno]>max)
   		{
   			max=Alltables[tableno].table_entry[i][colno];
   		}
   	}
   	return max;
}
int col_min(int tableno,int colno)
{
	int min=Alltables[tableno].table_entry[0][colno];
	for(int i=1;i<Alltables[tableno].row_count;i++)
   	{
   		if(Alltables[tableno].table_entry[i][colno]<min)
   		{
   			min=Alltables[tableno].table_entry[i][colno];
   		}
   	}
   	return min;
}

long long col_sum(int tableno,int colno)
{
	long long sum=0;
	for(int i=0;i<Alltables[tableno].row_count;i++)
   	{
   		sum+=Alltables[tableno].table_entry[i][colno];   		
   	}
   	return sum;
}

double col_avg(int tableno,int colno)
{
	long long sum=col_sum(tableno,colno);
	double avg=(double)sum/(double)Alltables[tableno].row_count;	
   	return avg;
}

void display_one_table(string tabname,vector < string > colms,int distinct_flag)
{
	int tableno,match,status=0;
	string ans;
	vector < int > colno;
	vector < int > colno_aggregate;
	tableno=get_tableno(tabname);
	//cout<<"tabno ::"<<tableno<<endl;
	if(tableno==-1)
	{
		cout<<"ERROR::tablename:"<<tabname<<" Does not exists"<<endl;
   		exit(0);
   	}
	if(colms.size()==1 && colms[0]=="*")
	{
		for(int j=0;j<Alltables[tableno].col_count;j++)
		{
			if(j!=Alltables[tableno].col_count-1)
			cout<<Alltables[tableno].table_name<<"."<<Alltables[tableno].column_names[j]<<",";
			else
			cout<<Alltables[tableno].table_name<<"."<<Alltables[tableno].column_names[j];
		}
		for(int i=0;i<Alltables[tableno].row_count;i++)
		{
		 	cout<<endl;
		   	for(int j=0;j<Alltables[tableno].col_count;j++)
		   	{	   			
				int x=Alltables[tableno].table_entry[i][j];	  			
	   			if(j!=Alltables[tableno].col_count-1)
	   			cout<<x<<",";	   	
	   			else
	   			cout<<x;		
	  		}
	   	}	
	   	cout<<endl;		
	}
	else 
	{
		vector < int > aggregate_flag;
		for(int i=0;i<colms.size();i++)
	   	{
	   		if(lowercase(colms[i].substr(0,4))=="max(")
    		{
    			string colname=colms[i].substr(4,colms[i].length()-5);	
    			colno_aggregate.push_back(get_colno_of_table(tableno,colname));
    			if(colno_aggregate[i]==-1)
	   			{
					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
					exit(0);
	   			}
	   			aggregate_flag.push_back(1);
   				status=1;
   			}   
    		else if(lowercase(colms[i].substr(0,4))=="min(")
    		{
   				string colname=colms[i].substr(4,colms[i].length()-5);
  				colno_aggregate.push_back(get_colno_of_table(tableno,colname));
    			if(colno_aggregate[i]==-1)
	   			{
					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
					exit(0);
	   			}
	   			aggregate_flag.push_back(2);
    			status=1;
   			}
   			else if(lowercase(colms[i].substr(0,4))=="sum(")
    		{
    			string colname=colms[i].substr(4,colms[i].length()-5);
   				colno_aggregate.push_back(get_colno_of_table(tableno,colname));
   				if(colno_aggregate[i]==-1)
				{
	   				cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
	   				exit(0);
				}
				aggregate_flag.push_back(3);
   				status=1;
    		}  	
    		else if(lowercase(colms[i].substr(0,4))=="avg(")
    		{
    			string colname=colms[i].substr(4,colms[i].length()-5);
    			colno_aggregate.push_back(get_colno_of_table(tableno,colname));
    			if(colno_aggregate[i]==-1)
	   			{
	   				cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
					exit(0);
				}
				aggregate_flag.push_back(4);
    			status=1;
    		}
   			else if(lowercase(colms[i].substr(0,6))=="count(")
    		{
    			string colname=colms[i].substr(6,colms[i].length()-7);
   				colno_aggregate.push_back(get_colno_of_table(tableno,colname));
   				if(colno_aggregate[i]==-1 && colname!="*")
   				{ 			
   					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
   					exit(0);	   				
   				}
   				aggregate_flag.push_back(5);
    			status=1;
    		} 	
    		else if(lowercase(colms[i].substr(0,9))=="distinct(")
    		{    		
    			
    			if((colms[i].find('(') != string::npos) && (colms[i].find(')') != string::npos))
    			{
    				string colname=colms[i].substr(9,colms[i].length()-10);
   					colno.push_back(get_colno_of_table(tableno,colname));		
   					if(colno[i]==-1 && colname!="*")
   					{ 			
   						cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
   						exit(0);	   				
   					}
   					distinct_flag=1;
    			}
    			else
				{
					cout<<"ERROR :: Distinct Statement is Invalid"<<endl;
					exit(0);
				}
    			
    		} 	
    		else 
    		{	 
    			if(status==0)
    			{  			
	   				colno.push_back(get_colno_of_table(tableno,colms[i]));		
	   				if(colno[i]==-1)
	   				{
	   					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<< colms[i]<<endl;
	   					exit(0);
	   				}
	   			}
	   			else
	   			{
	   				cout<<"ERROR :: You can not use aggregate function and projection operation at same time "<<endl;
					exit(0);
	   			}
	   			
	   		}
	   	}
	   	if(status==1)
	   	{
	   		for(int i=0;i<aggregate_flag.size();i++)
	   		{
	   			if(i!=aggregate_flag.size()-1)
	   			cout<<colms[i]<<",";
	   			else
	   			cout<<colms[i];
	   		}
	   		cout<<endl;
	   		for(int i=0;i<aggregate_flag.size();i++)
	   		{	   			
	   			if(aggregate_flag[i]==1)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<col_max(tableno,colno_aggregate[i])<<",";
   					else
   					cout<<col_max(tableno,colno_aggregate[i]); 					
	   			}
	   			else if(aggregate_flag[i]==2)
	   			{
	   				if(i!=aggregate_flag.size()-1)
   					cout<<col_min(tableno,colno_aggregate[i])<<","; 					
   					else
   					cout<<col_min(tableno,colno_aggregate[i]);
   					
	   			}
	   			else if(aggregate_flag[i]==3)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<col_sum(tableno,colno_aggregate[i])<<","; 					
   					else   					
   					cout<<col_sum(tableno,colno_aggregate[i]);					
	   			}
	   			else if(aggregate_flag[i]==4)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<col_avg(tableno,colno_aggregate[i])<<","; 					
   					else
   					cout<<col_avg(tableno,colno_aggregate[i]);   					
	   			}
	   			else if(aggregate_flag[i]==5)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<Alltables[tableno].row_count<<",";  				
    				else
    				cout<<Alltables[tableno].row_count;  				
	   			}
	   		}
	   		cout<<endl;	   		
	   	}
	   	else if(status==0)
	   	{
		   	for(int i=0;i<colno.size();i++)
		   	{
		   		if(i!=colno.size()-1)
		   		cout<<Alltables[tableno].table_name<<"."<<Alltables[tableno].column_names[colno[i]]<<",";
		   		else
				cout<<Alltables[tableno].table_name<<"."<<Alltables[tableno].column_names[colno[i]];
		   	}
		   	cout<<endl;
		   	vector<string> answer;
		   	
			for(int i=0;i<Alltables[tableno].row_count;i++)
			{
			   	ans="";
			   	for(int j=0;j<colno.size();j++)
			   	{
			   		int x=Alltables[tableno].table_entry[i][colno[j]];
			   		string s=NumberToString(x);
			  		if(j!=colno.size()-1)
			  		ans=ans+s+",";
			  		else
			  		ans=ans+s;
			   	} 		
			   	vector<string> ::iterator it;
				if(distinct_flag==0)
		  		{
		   			cout<<ans<<endl;
		   		}
		   		else
		 		{
		 			//cout<<"hello";
		   			match=0;
		   			for(it=answer.begin();it!=answer.end();it++)
		  			{
		  				//cout<<(*it)<<"BB"<<ans<<endl;
			   			if((*it).compare(ans)==0)
			   			{
			   				match=1;
			   				break;
						}
		   			}
		   			if(match==0)
		   			{
		   				answer.push_back(ans);
		   				cout<<ans<<endl;		   			
			   		}
			   }		
			}
		}		
	}
}


int col_max_1(table query_table,int colno)
{
	int max=query_table.table_entry[0][colno];
	for(int i=1;i<query_table.row_count;i++)
   	{
   		if(query_table.table_entry[i][colno]>max)
   		{
   			max=query_table.table_entry[i][colno];
   		}
   	}
   	return max;
}
int col_min_1(table query_table,int colno)
{
	int min=query_table.table_entry[0][colno];
	for(int i=1;i<query_table.row_count;i++)
   	{
   		if(query_table.table_entry[i][colno]<min)
   		{
   			min=query_table.table_entry[i][colno];
   		}
   	}
   	return min;
}

long long col_sum_1(table query_table,int colno)
{
	long long sum=0;
	for(int i=0;i<query_table.row_count;i++)
   	{
   		sum+=query_table.table_entry[i][colno];   		
   	}
   	return sum;
}

double col_avg_1(table query_table,int colno)
{
	long long sum=col_sum_1(query_table,colno);
	double avg=(double)sum/(double)query_table.row_count;	
   	return avg;
}
string search(string colname,vector <string> tables)
{
	if(colname.find('.') != string::npos)
	return colname;
	int conflict_count=0;
	string columnname=colname;
	for(int i=0;i<tables.size();i++)
   	{
   		int tableno=get_tableno(tables[i]);
   		for(int j=0;j<Alltables[tableno].col_count;j++)
   		{
   			int pos=colname.find(".");
			if(pos != string::npos)
			{
				colname=colname.substr(pos+1);
			}
   			if(Alltables[tableno].column_names[j]==colname)
   			{
   				colname=Alltables[tableno].table_name+"."+colname;	
   				conflict_count++;
   			}
   		}
   	}
   	if(conflict_count>1)
   	{
   		cout<<"Ambiguous Column Name : "<<columnname<<endl;
   		exit(0);
   	}
   	return colname; 
}
void display_result(string tabname,table query_table,vector < string > colms,int distinct_flag)
{
	int tableno,match,status=0;
	string ans;
	vector < int > colno;
	vector < int > colno_aggregate;
	if(colms.size()==1 && colms[0]=="*")
	{
		for(int j=0;j<query_table.col_count;j++)
		{
			int non_print_flag=0;
			for(int k=0;k<non_repeat_index.size();k++)
			{
				if(j==non_repeat_index[k])
				{
					non_print_flag=1;
					break;
				}
			}
			if(non_print_flag==0)
			{
				if(j!=query_table.col_count-1)
				cout<<query_table.column_names[j]<<",";
				else
				cout<<query_table.column_names[j];
			}
		}
		for(int i=0;i<query_table.row_count;i++)
		{
		 	cout<<endl;
		   	for(int j=0;j<query_table.col_count;j++)
		   	{	   			
				int x=query_table.table_entry[i][j];	  			
	   			
	   			int non_print_flag=0;
				for(int k=0;k<non_repeat_index.size();k++)
				{
					if(j==non_repeat_index[k])
					{
						non_print_flag=1;
						break;
					}
				}
				if(non_print_flag==0)
				{
	   				if(j!=query_table.col_count-1)
	   				cout<<x<<",";	   	
	   				else
	   				cout<<x;		
	  			}
	  		}
	   	}	
	   	cout<<endl;		
	}
	else 
	{
		vector < int > aggregate_flag;
		for(int i=0;i<colms.size();i++)
	   	{
	   		if(lowercase(colms[i].substr(0,4))=="max(")
    		{
    			string colname=colms[i].substr(4,colms[i].length()-5);	
    			colno_aggregate.push_back(get_colno(query_table,colname));
    			if(colno_aggregate[i]==-1)
	   			{
					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
					exit(0);
	   			}
	   			aggregate_flag.push_back(1);
   				status=1;
   			}   
    		else if(lowercase(colms[i].substr(0,4))=="min(")
    		{
   				string colname=colms[i].substr(4,colms[i].length()-5);
  				colno_aggregate.push_back(get_colno(query_table,colname));
    			if(colno_aggregate[i]==-1)
	   			{
					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
					exit(0);
	   			}
	   			aggregate_flag.push_back(2);
    			status=1;
   			}
   			else if(lowercase(colms[i].substr(0,4))=="sum(")
    		{
    			string colname=colms[i].substr(4,colms[i].length()-5);
   				colno_aggregate.push_back(get_colno(query_table,colname));
   				if(colno_aggregate[i]==-1)
				{
	   				cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
	   				exit(0);
				}
				aggregate_flag.push_back(3);
   				status=1;
    		}  	
    		else if(lowercase(colms[i].substr(0,4))=="avg(")
    		{
    			string colname=colms[i].substr(4,colms[i].length()-5);
    			colno_aggregate.push_back(get_colno(query_table,colname));
    			if(colno_aggregate[i]==-1)
	   			{
	   				cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
					exit(0);
				}
				aggregate_flag.push_back(4);
    			status=1;
    		}
   			else if(lowercase(colms[i].substr(0,6))=="count(")
    		{
    			string colname=colms[i].substr(6,colms[i].length()-7);
   				colno_aggregate.push_back(get_colno(query_table,colname));
   				if(colno_aggregate[i]==-1 && colname!="*")
   				{ 			
   					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
   					exit(0);	   				
   				}
   				aggregate_flag.push_back(5);
    			status=1;
    		} 	
    		else if(lowercase(colms[i].substr(0,9))=="distinct(")
    		{    		
    			
    			if((colms[i].find('(') != string::npos) && (colms[i].find(')') != string::npos))
    			{
    				string colname=colms[i].substr(9,colms[i].length()-10);
    				colno.push_back(get_colno(query_table,colname));		
   					if(colno[i]==-1 && colname!="*")
   					{ 			
   						cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<<colname<<endl;
   						exit(0);	   				
   					}
   					distinct_flag=1;
    			}
    			else
				{
					cout<<"ERROR :: Distinct Statement is Invalid"<<endl;
					exit(0);
				}
    			
    		} 	
    		else 
    		{	 
    			if(status==0)
    			{  			
	   				colno.push_back(get_colno(query_table,colms[i]));	
	   				if(colno[i]==-1)
	   				{
	   					cout<<"ERROR:: Tablename : "<<tabname<<" Does not have Columnname : "<< colms[i]<<endl;
	   					exit(0);
	   				}
	   			}
	   			else
	   			{
	   				cout<<"ERROR :: You can not use aggregate function and projection operation at same time "<<endl;
					exit(0);
	   			}
	   			
	   		}
	   	}
	   	if(status==1)
	   	{
	   		for(int i=0;i<aggregate_flag.size();i++)
	   		{
	   			if(i!=aggregate_flag.size()-1)
	   			cout<<colms[i]<<",";
	   			else
	   			cout<<colms[i];
	   		}
	   		cout<<endl;
	   		for(int i=0;i<aggregate_flag.size();i++)
	   		{	   			
	   			if(aggregate_flag[i]==1)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<col_max_1(query_table,colno_aggregate[i])<<",";
   					else
   					cout<<col_max_1(query_table,colno_aggregate[i]); 					
	   			}
	   			else if(aggregate_flag[i]==2)
	   			{
	   				if(i!=aggregate_flag.size()-1)
   					cout<<col_min_1(query_table,colno_aggregate[i])<<","; 					
   					else
   					cout<<col_min_1(query_table,colno_aggregate[i]);
   					
	   			}
	   			else if(aggregate_flag[i]==3)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<col_sum_1(query_table,colno_aggregate[i])<<","; 					
   					else   					
   					cout<<col_sum_1(query_table,colno_aggregate[i]);					
	   			}
	   			else if(aggregate_flag[i]==4)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<col_avg_1(query_table,colno_aggregate[i])<<","; 					
   					else
   					cout<<col_avg_1(query_table,colno_aggregate[i]);   					
	   			}
	   			else if(aggregate_flag[i]==5)
	   			{
	   				if(i!=aggregate_flag.size()-1)
	   				cout<<query_table.row_count<<",";  				
    				else
    				cout<<query_table.row_count;  				
	   			}
	   		}
	   		cout<<endl;	   		
	   	}
	   	else if(status==0)
	   	{
		   	for(int i=0;i<colno.size();i++)
		   	{
		   		if(i!=colno.size()-1)
		   		cout<<query_table.column_names[colno[i]]<<",";
		   		else
				cout<<query_table.column_names[colno[i]];
		   	}
		   	cout<<endl;
		   	vector<string> answer;
		   	
			for(int i=0;i<query_table.row_count;i++)
			{
			   	ans="";
			   	for(int j=0;j<colno.size();j++)
			   	{
			   		int x=query_table.table_entry[i][colno[j]];
			   		string s=NumberToString(x);
			  		if(j!=colno.size()-1)
			  		ans=ans+s+",";
			  		else
			  		ans=ans+s;
			   	} 		
			   	vector<string> ::iterator it;
				if(distinct_flag==0)
		  		{
		   			cout<<ans<<endl;
		   		}
		   		else
		 		{
		 			//cout<<"hello";
		   			match=0;
		   			for(it=answer.begin();it!=answer.end();it++)
		  			{
		  				//cout<<(*it)<<"BB"<<ans<<endl;
			   			if((*it).compare(ans)==0)
			   			{
			   				match=1;
			   				break;
						}
		   			}
		   			if(match==0)
		   			{
		   				answer.push_back(ans);
		   				cout<<ans<<endl;		   			
			   		}
			   }		
			}
		}		
	}
}



void readmdfile()
{
	// cout<<"hello staart"<<endl;
    string line;
	int begin_flag=0,col_flag=0,i;
    ifstream mdfile("metadata.txt");
	while(getline(mdfile, line))
    {
   		// cout<<line<<endl;
   		string pattern="\f\n\r\t\v";
   		line=line.substr(0,line.find_last_not_of(pattern)+1);
   		if(line.find("<begin_table>") == 0)
        {
        	begin_flag=1;
        	// cout<<"hello inside begin\n";
        }
        else if(line.find("<end_table>") == 0)
        {
        		// cout<<"hello inside end\n";
        	string tabline,filename;
        	filename=Alltables[table_count].table_name+".csv";
        	ifstream tabfile(filename.c_str());
        	while(getline(tabfile,tabline))
        	{
        		//cout<<tabline<<endl;
        		tabline.erase(remove(tabline.begin(),tabline.end(), '\"' ),tabline.end());
        		vector<string> tab_entry = split(tabline,',');
        		vector<int> tabrow_entry;
               	for(i=0;i<tab_entry.size();i++)
                {
                	tabrow_entry.push_back(atoi(tab_entry[i].c_str()));
                }  
               	Alltables[table_count].table_entry.push_back(tabrow_entry);	
               	Alltables[table_count].row_count++;
        	}
        	tabfile.close();
        	col_flag=0;
        	// cout<<Alltables.size()<<"  "<<Alltables[table_count].table_name<<endl;
        }
        else if(begin_flag==1)
        {
        	table tab;
        	tab.table_name=line;
        	tab.row_count=0;
        	tab.col_count=0;
        	++table_count;
   	     	Alltables.push_back(tab);
        	begin_flag=0;
        	col_flag=1;
        }
        else if(col_flag==1)
       	{
      		Alltables[table_count].column_names.push_back(line);
       		Alltables[table_count].col_count++;
        }
        // cout<<"hello inside "<<line<<endl;
   	} 
   	// cout<<"hello"<<endl;
	mdfile.close();
}
int same(string left_operand,string right_operand)
{
	int pos=left_operand.find(".");
	if(pos != string::npos)
	{
		left_operand=left_operand.substr(pos+1);
	}
	int pos1=right_operand.find(".");
	if(pos1 != string::npos)
	{
		right_operand=right_operand.substr(pos+1);
	}
//	cout<<"left_operand : "<<left_operand<<" right_operand : "<<right_operand<<endl;
	if(left_operand==right_operand)
	return 1;
	else
	return 0;
}
void parse(string input)
{
	int i,select_flag=0,from_flag=0,and_flag=0,or_flag=0,where_flag=0,star_flag=0,n,distinct_flag=0,join_flag=0;
	int start;
	string word="";
    for(i=0;i<input.size();i++)
    {
    	//cout<<distinct_flag;
       	if(input[i] != ' ')
        {
        	word=word+input[i];
        }
        else if(word!="")
        {
        	if(lowercase(word) == "select")
        	{
        		word="select ";
        		select_flag=1;        	
        	}
        	else if(lowercase(word) == "distinct")
            {
            	word="distinct";
            	distinct_flag++;
            }
        	else if(lowercase(word) == "from")
            {
            	word="from";
            	from_flag=1;
            }
        	else if(lowercase(word) == "where")
           	{
           	 	word="where";
           	 	where_flag=1;
           	}
        	else if(lowercase(word) == "and")
            {
            	word="and";
            	and_flag=1;
        	}
        	else if(lowercase(word) == "or")
          	{	
          		word="or";  
          		or_flag=1;
          	}          
         	query.push_back(word);
          	word="";
 		}       
 	}
 	if(word!="")
    query.push_back(word);
    /*for(i=0; i<query.size(); i++)
    {
     	cout<<query[i]<<endl;
    }*/
   	if(select_flag==0) 
    {
    	cout<<"ERROR:: Select Clause Missing"<<endl;
    	exit(0);
    }
    if(from_flag==0)
    {
    	cout<<"ERROR:: From Clause Missing"<<endl;
    	exit(0);	
    }
    if(distinct_flag>1)
    {
     	cout<<"ERROR :: Distinct Statement is Invalid"<<endl;
		exit(0);
    }
    if(distinct_flag==1)
    {
    	for(i=0; i<query.size(); i++)
    	{
     		if(query[i]=="distinct" && query[i+1].find("distinct") != string::npos)
     		{
     			cout<<"ERROR :: Distinct Statement is Invalid"<<endl;
				exit(0);
     		}
    	}
    }
    if(distinct_flag==0)
    {
    	start=1;
  	}
    else
    {
    	start=2;
    }
    string colnames="";
    for(i=start;i<query.size();i++)
    {
    	if(query[i].compare("from")==0) 
    	{	
    		break;
    	}	
    	else
    	{
    		colnames+=query[i];
    	}
    }   
    n=i+1;     //n stores start of table names index
    if(colnames=="")
    {
    	cout<<"ERROR:: No Column to Display"<<endl;
    	exit(0);
    }
  //  cout<<colnames<<endl;
    vector<string> colms;
   	if(colnames.compare("*")==0)
    {
    	star_flag=1;
    	string s="*";
    	colms.push_back(s);
    }
    else
    {
    	colms=split(colnames,',');
    }
    
    string tabnames="";
    vector<string> tabs;
    if(where_flag==0)
	{
   		for(i=n;i<query.size();i++)
    	{
    		tabnames+=query[i];
    	}
    	tabs=split(tabnames,',');
    	if(tabs.size()==1)
    	{
    		display_one_table(tabs[0],colms,distinct_flag);
    	}
    	else
    	{
    		//cross product
    		table temp_table=cross_product(tabs);
    	//	temp_table.table_name="Pr";
    		
    		for(int j=0;j<temp_table.col_count;j++)
			{
				if(j!=temp_table.col_count-1)
				cout<<temp_table.column_names[j]<<",";
				else
				cout<<temp_table.column_names[j];
			}
			for(int i=0;i<temp_table.row_count;i++)
			{
		 		cout<<endl;
		   		for(int j=0;j<temp_table.col_count;j++)
		   		{	   			
					int x=temp_table.table_entry[i][j];	  			
	   				if(j!=temp_table.col_count-1)
	   				cout<<x<<",";	
	   				else
	   				cout<<x;   			
	  			}
	   		}	
	   		cout<<endl;
	   	//	cout<<"rowCount:: "<<temp_table.row_count;	 			
    	}
    }
    else if(where_flag==1)
    {
    	for(i=n;i<query.size();i++)
    	{
    		if(query[i].compare("where")==0) 
    		{	
    			break;
    		}	
    		else
    		{
    			tabnames+=query[i];
    		}
    	}
    	   
    	tabs=split(tabnames,',');
    	int after_where_index=i+1;
    	string condition="";
    	vector < string > Allconditions;
    	vector < string > operation;
    	for(i=after_where_index;i<query.size();i++)
    	{
    		if(query[i].compare("and")==0) 
    		{	
    			operation.push_back("and");
    			Allconditions.push_back(condition);
    			condition="";
    		}	
    		else if(query[i].compare("or")==0) 
			{
				operation.push_back("or");
				Allconditions.push_back(condition);
				condition="";
			}
			else    	
    		{
    			condition+=query[i];
    		}
    	}
    	
    	Allconditions.push_back(condition);
    	table temp_result;
    	if(tabs.size()==1)
    	{
    		int tableno=get_tableno(tabs[0]);
    		if(tableno==-1)
			{	
				cout<<"ERROR:: Tablename: "<<tabs[i]<<" Does not exists"<<endl;
   				exit(0);
   			}
    		temp_result=Alltables[tableno];
    		for(int j=0;j<Alltables[tableno].col_count;j++)
			{
				temp_result.column_names[j]=Alltables[tableno].table_name+"."+Alltables[tableno].column_names[j];	
			}	
    	}
    	else
    	{
    		//cross product
    		temp_result=cross_product(tabs);
    	}
    	table where_result=temp_result;
    	where_result.table_entry.clear();
    	where_result.row_count=0;
    	vector < int > All_condition_output;
    	vector < string > operation1;
    	for(int k=0;k<temp_result.row_count;k++)
		{   /*************************/    	
			string left_operand,right_operand;
			int op=1;
			All_condition_output.clear();
			operation1=operation;
			for(i=0;i<Allconditions.size();i++)
	   	 	{
	   	 		
		   		int Condition_flag=0,left_value,right_value;
		   		for(int j=0;j<Allconditions[i].size();j++)
		   		{
		   			 
		 			if(Allconditions[i][j] == '>' && Allconditions[i][j+1]=='=')
		    		{
		    			Condition_flag=1;
		    			left_operand=Allconditions[i].substr(0,j);
		    			right_operand=Allconditions[i].substr(j+2);
		    		//	cout<<"left opearnd : "<<left_operand<<" Right operand : "<<right_operand<<endl;
		    	    	break;
		    		}
		    		else if(Allconditions[i][j] == '>')
		    		{
		    			Condition_flag=2;
		    			left_operand=Allconditions[i].substr(0,j);
		    			right_operand=Allconditions[i].substr(j+1);
		    	//		cout<<"left opearnd : "<<left_operand<<" Right operand : "<<right_operand<<endl;
		    			break;
		    		}	
		    		else if(Allconditions[i][j] == '<' && Allconditions[i][j+1]=='=')
		    		{
		    			Condition_flag=3;
		    			left_operand=Allconditions[i].substr(0,j);
		    			right_operand=Allconditions[i].substr(j+2);
		    	//		cout<<"left opearnd : "<<left_operand<<" Right operand : "<<right_operand<<endl;
		    			break;
		    		}	
		    		else if(Allconditions[i][j] == '<')
		    		{
		    			Condition_flag=4;
		    			left_operand=Allconditions[i].substr(0,j);
		    			right_operand=Allconditions[i].substr(j+1);
		    		//	cout<<"left opearnd : "<<left_operand<<" Right operand : "<<right_operand<<endl;
		    			break;
		    		}
		    		else if(Allconditions[i][j] == '!' && Allconditions[i][j+1] == '=')
		    		{
		    			Condition_flag=5;
		    			left_operand=Allconditions[i].substr(0,j);
		    			right_operand=Allconditions[i].substr(j+2);
		    //			cout<<"left opearnd : "<<left_operand<<" Right operand : "<<right_operand<<endl;
		    			break;
		    		}		
		    		else if(Allconditions[i][j] == '=')
		    		{
		    			Condition_flag=6;
		    			left_operand=Allconditions[i].substr(0,j);
		    			right_operand=Allconditions[i].substr(j+1);
		    			join_flag=same(left_operand,right_operand);
		    	//		cout<<"left opearnd : "<<left_operand<<" Right operand : "<<right_operand<<endl;
		    			break;
		    		}	
		    	}
		    	
		    	if(is_digits(left_operand))
		    	{
		    //		cout<<"left opearnd is value: "<<left_operand<<endl;
		    		left_value=atoi(left_operand.c_str());
		    	}
		    	else
		    	{
		    		left_operand=search(left_operand,tabs);
		    		int left_op_colno=get_colno(temp_result,left_operand);
		    		if(left_op_colno==-1)
					{
		   				cout<<"ERROR:: Columnname : "<< left_operand <<" Does not Exists in Specified Table"<<endl;
		   				exit(0);
					}
					left_value=temp_result.table_entry[k][left_op_colno];
		    	}		
		    	if(is_digits(right_operand))
		    	{
		    //		cout<<"right opearnd is value: "<<right_operand<<endl;
		    		right_value=atoi(right_operand.c_str());
		   		}
	  			else
		    	{
		    		right_operand=search(right_operand,tabs);
		    		int right_op_colno=get_colno(temp_result,right_operand);
		    		
		  			if(right_op_colno==-1)
					{
		   				cout<<"ERROR:: Columnname : "<< right_operand <<" Does not Exists in Specified Table"<<endl;
						exit(0);
					}
					if(Condition_flag==6 && join_flag==1)
		    		non_repeat_index.push_back(right_op_colno);
					right_value=temp_result.table_entry[k][right_op_colno];
		    	}
		    	int output=0;			
		    	if(Condition_flag==1 && left_value >= right_value)
				{
					output=1;			
				}   
				else if(Condition_flag==2 && left_value > right_value)
				{
					output=1;			
				}  
				else if(Condition_flag==3 && left_value <= right_value)
				{
					output=1;			
				}  
				else if(Condition_flag==4 && left_value < right_value)
				{
					output=1;			
				}  
				if(Condition_flag==5 && left_value != right_value)
				{
					output=1;			
				}  
				else if(Condition_flag==6 && left_value == right_value)
				{
					output=1;			
				}  
				All_condition_output.push_back(output);
			}	
			int and_index;
			int l=0;
	
			while(l<operation1.size())
			{
				if(operation1[l].compare("and")==0)
				{
					All_condition_output[l+1]= All_condition_output[l] & All_condition_output[l+1];
					All_condition_output.erase(All_condition_output.begin() + l);
					operation1.erase(operation1.begin() + l);
					l--;
				}
				l++;
			}	
			
			
			
			int final_output=All_condition_output[0];
			for(int g=1;g<All_condition_output.size();g++)
			{
				final_output= final_output || All_condition_output[g];
			}
		//	cout<<final_output<<endl;
			
			if(final_output ==1)
			{					   			
				where_result.table_entry.push_back(temp_result.table_entry[k]);	
				where_result.row_count++;  						   				  			
			}
    
    	}	   		 
	   for(int i=0;i<colms.size();i++)
	   {
	   		if(colms.size()==1 && colms[0]=="*")
	   		{
	   			
	   		}
	   		else
	   		colms[i]=search(colms[i],tabs);
	   }
	   display_result(tabs[0],where_result,colms,distinct_flag);			    	   	
    }
}

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		cout<<"ERROR :: Number Of Arguments are Invalid "<<endl;
		exit(0);
	}
	else  
	{
		readmdfile();
		string query=argv[1];
		int pos=query.find(';');
		if(pos != string::npos)
		{
			query=query.substr(0,pos);
		}
		// cout<<query;
		parse(query);
	}
    return 0;
}


