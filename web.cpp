#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
#include "web.h"
Web::Web()
{

}

Web::~Web()
{

}

bool Web::read_graph(const char *filename)
{
    ifstream ifile(filename);
    if( ifile.fail()){
        cout << "Couldn't open file" << endl;
        return false;
    }
    int numPages;
    ifile>>numPages;
    if( ifile.fail()){
        return false;
    }
    string blank;
    getline(ifile,blank);
    string pageid;
    int page;
    string rank;
    string url;
    string furl;
    string vector1;
    int v;

    for(int z = 0; z<numPages; z++){
        stringstream sb;
        stringstream urla;
        getline(ifile,pageid);
        sb<<pageid;
        sb>>page; 
        if (sb.fail()){
            return false;
        }

        getline(ifile,url);
        urla<<url;
        urla>>furl;
        if(ifile.fail()){
            return false;
        }

        getline(ifile,rank);
        if(ifile.fail()){
            return false;
        }

        stringstream ne(rank);
        double r = 0.0;
        ne >> r;
        if (ne.fail()){
            return false;
        }

        getline(ifile,vector1);
        if(ifile.fail()){
            return false;
        }
        vector<int> temp;
        stringstream ss(vector1);
        if (ss.fail()){
            return false;
        }
        while(ss>>v){
            if(ss.fail()){
                return false;
            }
            temp.push_back(v);
        }

        Page p(page,furl,temp,r);
        pageList.push_back(p);

        if (ifile.fail()){
            return false;
        }

    }
    return true;
}

bool Web::write_graph(const char *filename)
{   //catch an error
    ofstream write(filename);
    if(write.fail()){
        cout << "Couldn't output file" << endl;
    }
 
    write << pageList.size()<<'\n';
    for(unsigned int i=0; i<pageList.size(); i++){
        write << i << endl;
        write << '\t' << pageList[i].geturl() << endl;
        write << '\t' << pageList[i].getPagerank() << endl;
        write << '\t';
        for(unsigned int j=0; j<pageList[i].getoutbound()->size(); j++){
            write << pageList[i].getoutbound()->at(j) << " ";
        }
        write<<endl;
    }
    return true;
}

//calculating pagerank by assigning random walkers to each page, and then simulating how they move
void Web::calculate_rank(int S,int N)
{
    int walkers[N];
    int nodes = numberPages();
    int looper = 0;
    int* counter = new int[nodes];
    for(int j=0; j<N; j++){
        walkers[j] = looper;
        looper++;
        if(looper>=nodes){looper=0;}
    }
    // the walkers walk around randomly
    for(int a=0; a<S; a++){
        for(int i=0; i<N; i++){
            vector<int>* temp = pageList[walkers[i]].getoutbound();
            if(temp->size()!=0){
                walkers[i]= (*temp)[(rand()% temp->size())];
            }
        }
    }
    //count how many walkers are on each page
    for(int i=0; i<nodes; i++) {
        counter[i] = 0;
    }
    for(int j=0; j<N; j++){
        for(int b=0; b<nodes; b++) {
            if(walkers[j] == b){
                counter[b]++;
            }
        }
    }
    //calculate pagerank
    for(int i=0; i<nodes; i++){
        pageList[i].setPagerank((double)counter[i]/(double)N);
    }
    delete[] counter;
}
