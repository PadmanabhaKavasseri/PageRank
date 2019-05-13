#ifndef PAGE_H
#define PAGE_H
#include <string>
using std::string;
#include<vector>
using std::vector;

class Page {
public:
    Page(int pageid1, string url1, vector<int> outbound1,double pagerank1);
    int getPageid() { return pageid; }
    void setPageid(int id) { pageid = id;}
    string geturl() {return url;}
    void setPageid(string gurl) {url= gurl;}

    vector<int>* getoutbound() {return &outbound;}
    void setPageid(vector<int> goutbound) { outbound=goutbound  ;}

    double getPagerank() {return pagerank;}
    void setPagerank(double gprank) {pagerank= gprank;}
private:
    int pageid;
    string url;
    vector <int> outbound;
    double pagerank;
};
#endif