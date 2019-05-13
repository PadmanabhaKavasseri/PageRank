#include "page.h"

Page::Page(int pageid1, string url1, vector<int> outbound1,double pagerank1)
{
    pageid = pageid1;
    url = url1;
    outbound = outbound1;
    pagerank = pagerank1;
}