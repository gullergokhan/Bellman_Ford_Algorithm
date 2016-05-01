#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using namespace std;

const int inf=9999;

//yeni veri tipleri oluþturduk edge ve graph 
struct Edge{
	int kaynak, hedef, uzaklik;
};
struct Graph{
	int V,E; 
	Edge* edge;
};
//Graph çizmek için fonksiyon tanýmlandý
struct Graph* graphCiz(int V, int E){
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
 
    return graph;
}
//diziyi yazdýrmak için bir fonksiyon tanýmlandý
void ArrYaz(int uzunluk[], int n)
{
    cout<<"Kaynaktan hedefe olan uzaklik:"<<endl;
    for (int i = 0; i < n; ++i)
        cout<< i<<" -> "<< uzunluk[i]<<endl;
}
//Bellman ford algoritmasý için bir fonksiyon tanýmlandý
void BellmanFord(struct Graph* graph, int kaynak)
{
    int V = graph->V;
    int E = graph->E;
    int uzunluk[V];
 
    // kaynak noktadan sonrasýndaki tüm noktalara olaz uzaklýðý sonsuz olarak belirledik
    for (int i = 0; i < V; i++)
        uzunluk[i] = inf;
    uzunluk[kaynak] = 0;
 
    // en kýsa yol bulundu
    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].kaynak;
            int v = graph->edge[j].hedef;
            int uzaklik = graph->edge[j].uzaklik;
            if (uzunluk[u] != inf && uzunluk[u] + uzaklik <= uzunluk[v])
                uzunluk[v] = uzunluk[u] + uzaklik;
        }
    }
 
    // Negatif uzunluk olup olmadýðý kontrol ediliyor
    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].kaynak;
        int v = graph->edge[i].hedef;
        int uzaklik = graph->edge[i].uzaklik;
        if (uzunluk[u] != inf && uzunluk[u] + uzaklik < uzunluk[v])
            cout<<"Graph negatif deger donduruyor!";
    }
 
    ArrYaz(uzunluk, V);
 
    return;
}

int main()
{
    //örnek bir graph tanýmý yaptýk
    int V = 6; // noktalarýn sayýsý
    int E = 9; // edgelerin sayýsý
	struct Graph* graph = graphCiz(V, E);
 
    // Edgeleri ekliyoruz
    // (a-b) arasý 0-1
    graph->edge[0].kaynak = 0;
    graph->edge[0].hedef = 1;
    graph->edge[0].uzaklik = 3;
 
    // (a-c) arasý 0-2
    graph->edge[1].kaynak = 0;
    graph->edge[1].hedef = 2;
    graph->edge[1].uzaklik = 3;
 
    // (b-c) arasý 1-2
    graph->edge[2].kaynak = 1;
    graph->edge[2].hedef = 2;
    graph->edge[2].uzaklik = 1;
 
    // (b-d) arasý 1-3
    graph->edge[3].kaynak = 1;
    graph->edge[3].hedef = 3;
    graph->edge[3].uzaklik = 5;
 
    // (c-d) arasý 2-3
    graph->edge[4].kaynak = 2;
    graph->edge[4].hedef = 3;
    graph->edge[4].uzaklik = 8;
 
    // (c-e) arasý 2-4
    graph->edge[5].kaynak = 2;
    graph->edge[5].hedef = 4;
    graph->edge[5].uzaklik = 10;
 
    // (d-e) arasý 3-4
    graph->edge[6].kaynak = 3;
    graph->edge[6].hedef = 4;
    graph->edge[6].uzaklik = 2;
 
    // (d-f) arasý 3-5
    graph->edge[7].kaynak = 3;
    graph->edge[7].hedef = 5;
    graph->edge[7].uzaklik = 6;
    
    // (e-f) arasý 4-5
    graph->edge[8].kaynak = 4;
    graph->edge[8].hedef = 5;
    graph->edge[8].uzaklik = 3;
    cout<<"baslangic adres numarasini giriniz(0-5 araliginda):"<<endl;
    int k;
	cin>>k;
	BellmanFord(graph, k);
 
    return 0;
}
