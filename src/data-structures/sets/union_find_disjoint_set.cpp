#define MAX 40010

class UFDS {
public:
    int parents[MAX];
    int heights[MAX];

    UFDS(int size)
    {
        for(int i = 0; i < size; ++i)
        {
            heights[i] = 1;
            parents[i] = i;
        }
    }

    inline int find_set(int i) // find the set of node i
    {
        if(parents[i] != i)
            parents[i] = find_set(parents[i]);
        return parents[i];
    }

    inline bool same_set(int x, int y) // checks if x and y are in the same set
    {
        return find_set(x) == find_set(y);
    }

    void union_set(int x, int y) // unite x and y in the same set
    {
        int root1 = find_set(x), root2 = find_set(y);

        if(root1 != root2) // x and y are not in the same set
        {
            // The larger set absorb the smaller set
            if(heights[root1] < heights[root2]) swap(root1, root2);

            parents[root2] = root1;
            heights[root1] += heights[root2];
        }
    }
};


int main()
{
    return 0;
}

/*
    Tested on: UVA599, UVA10583, UVA11503, URI1764
*/
