#include "../common.h"

typedef struct {
    ii vertices;
    int w;
} edge;

vvi G;
vector<edge> E;
vi P /* PARENT */, SZ /* SIZE */, L /* LEVEL */;
vvi A /* ANCESTOR */;
vi CH /* CHAIN */, CHP /* CHAIN POSITION */, CLE /* CHAIN LINK EDGE */;
vi  CHI /* CHAIN INDEX */, SGT /* SEGMENT TREE */;

void update_min(int& current_min, int candidate)
{
    if (candidate == -1)
        return;

    if (current_min == -1)
        current_min = candidate;

    if (candidate != -1 && E[candidate].w < E[current_min].w)
        current_min = candidate;
}

void update_sgt_node(int node)
{
    int min = -1;
    update_min(min, SGT[2*node + 1]);
    update_min(min, SGT[2*node + 2]);
    SGT[node] = SGT[min];
}

void build_sgt(int i, int j, int node)
{
    if (i > j) return;
    if (i == j) { SGT[node] = CH[i]; return; }

    int mid = (i+j)/2;
    build_sgt(i, mid, 2*node + 1);
    build_sgt(mid+1, j, 2*node + 2);
    update_sgt_node(node);
}

void update_sgt(int e, int i, int j, int node)
{
    if (i >= j) return;

    int mid = (i+j)/2;

    if (e <= mid)
        update_sgt(e, i, mid, 2*node + 1);
    else
        update_sgt(e, mid+1, j, 2*node + 2);

    update_sgt_node(node);
}

int read_sgt(int l, int r, int i, int j, int node)
{
    if (l == i && r == j) return SGT[node];

    int mid = (i+j)/2;

    if (r <= mid) return read_sgt(l, r, i, mid, 2*node + 1);
    if (l > mid) return read_sgt(l, r, mid+1, j, 2*node + 2);

    int left = read_sgt(l, mid, i, mid, 2*node + 1);
    int right = read_sgt(mid+1, r, mid+1, j, 2*node + 2);
    return (E[left].w < E[right].w) ? left : right; 
}

void dfs(int root)
{
    sti st;
    st.push(root);
    L[root] = 0;
    P[root] = -1;

    while (!st.empty())
    {
        int u = st.top();
        bool children_left_to_process = false;

        TR(e, G[u])
        {
            int v = OTHER(E[e].vertices, u);
            if (v != P[u] && P[v] == -1)
            {
                children_left_to_process = true;
                P[v] = u;
                L[v] = L[u] + 1;
                st.push(v);
                break;
            }
        }

        if (children_left_to_process)
            continue;

        // Add the number of child nodes
        TR(e, G[u])
        {
            int v = OTHER(E[e].vertices, u); 
            if (v != P[u])
                SZ[u] += SZ[v];
        }

        // Count self
        SZ[u] += 1;
        st.pop();
    }
}

void hld(int u, int chain, int& next_chain_index)
{
    CHI[u] = chain;

    int largest_subtree = -1, edge_index = -1;
    TR(e, G[u])
    {
        int v = OTHER(E[e].vertices, u);
        if (v != P[u] && (largest_subtree == -1 || SZ[v] > SZ[largest_subtree]))
        {
            largest_subtree = v;
            edge_index = e;
        }
    }

    if (largest_subtree != -1)
    {
        CHP[largest_subtree] = CH.size();
        CH.PUSH(edge_index);
        hld(largest_subtree, chain, next_chain_index);

        TR(e, G[u])
        {
            int v = OTHER(E[e].vertices, u);
            if (v != P[u] && v != largest_subtree)
            {
                CHP[v] = CH.size();
                CH.PUSH(e);
                CLE[next_chain_index] = e;
                hld(v, next_chain_index, ++next_chain_index);
            }
        }
    }
}

void build_lca_sparse_table()
{
    REPI(j, 0, log2(G.size()))
    REP(i, 1, G.size())
    {
        if (j == 0)
            A[i][j] = P[i];
        else
            A[i][j] = A[i][j-1] == -1 ? -1 : A[A[i][j - 1]][j - 1];
    }
}

int lca(int u, int v)
{
    // Make sure v is deeper than u
    if (L[u] > L[v]) swap(u, v);

    while (L[v] > L[u])
    { 
        // start from v's second ancestor, as first ancestor
        // can't be higher than u if L[v] > L[u]
        int j = 1;

        // find v's ancestor that is just higher than u
        while (A[v][j] != -1 && L[A[v][j]] >= L[u])
            j++;
        
        // (j-1)th ancestor either lower than or at same level as u
        v = A[v][j-1]; 
    }

    // Now v and u are on the same level
    while (v != u)
    {
        // find j such that (j-1)th ancestor is different for u and v
        int j = 1;
        while (A[v][j] != A[u][j]) j++;
        v = A[v][j-1];
        u = A[u][j-1];
    }

    return v;
}

int min_weight_along_path(int u, int a)
{
    if (u == a)
        return -1;

    if (CHI[u] == CHI[a])
        return read_sgt(CHP[a] + 1, CHP[u], 0, CH.size() - 1, 0);

    // The edge that connects chain's head to rest of the tree
    int ei = CLE[CHI[u]];
    auto e = E[ei];

    // Split path (u -> a) into (u->child)--e-->(parent->a)
    int child = (e.vertices.first == P[e.vertices.second]) ? e.vertices.second : e.vertices.first;
    int parent = OTHER(e.vertices, child);

    int min = -1;
    update_min(min, min_weight_along_path(u, child));
    update_min(min, ei);
    update_min(min, min_weight_along_path(parent, a));
    return min;
}

int main()
{
    CASE
    {
        GET(N);
        RES(G, N+1);

        RES(E);
        REP(N-1)
        {
            GET(a, b, c);
            edge e = {PAIR(a, b), c};
            G[a].PUSH(E.size());
            G[b].PUSH(E.size());
            E.PUSH(e);
        }

        int root = 1;

        RES(P, N+1, -1); RES(SZ, N+1); RES(L, N+1);
        dfs(root);

        RES(CH); RES(CHI, N+1, -1); RES(CHP, N+1, -1), RES(CLE, N+1, -1);
        int next_chain_index = 1;
        hld(root, 0, next_chain_index);

        RES(SGT, 4*CH.size());
        build_sgt(0, CH.size() - 1, 0);

        RES(A, N+1, vi(log2(N) + 1, -1));
        build_lca_sparse_table();

        while (true)
        {
            string command;
            cin>>command;

            if (command == "CHANGE")
            {
                GET(e, c); e--;
                E[e].w = c;
                
                // Fix segment tree if both the vertices are on the same CH
                int u = E[e].vertices.first;
                int v = E[e].vertices.second;
                if (CHI[u] == CHI[v])
                    update_sgt(MAX(CHP[u], CHP[v]), 0, CH.size() - 1, 0);
            }
            else if (command == "QUERY")
            {
                GET(u, v);
                int l = lca(u, v);
                int min = -1;
                update_min(min, min_weight_along_path(u, l));
                update_min(min, min_weight_along_path(v, l));
                printf("%d\n", E[min].w);
            }
            else break;
        }
    }    
    return 0;
}