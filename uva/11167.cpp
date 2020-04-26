#include "../common.h"

#define MAXN 105

typedef struct
{
    int from;
    int to;
    int capacity;
    int flow;
} edge;
vvi G(505);
vector<edge> edges;

int time_slot_index(int time_slot)
{
    return time_slot + MAXN;
}

int time_slot(int index)
{
    return index - MAXN;
}

int monkey(int index)
{
    return index - 2;
}

int monkey_index(int monkey)
{
    return monkey + 2;
}

inline void add_edge(const edge &e)
{
    int edge_index = edges.size();
    edges.push_back(e);
    G[e.from].push_back(edge_index);
    G[e.to].push_back(edge_index);
}

int compute_max_flow(
    const int source,
    const int target)
{
    int flow = 0;
    while (true)
    {
        // queue containing vertices along with the maximum
        // permissible flow on the path source ----> vertex
        qii bfs_queue;
        bfs_queue.push(PAIR(source, INF));

        // edge leading to a particular vertex on the
        // shorted path from source
        mii edge_leading_to;

        int increase_in_flow = 0;
        while (!bfs_queue.empty())
        {
            auto um = bfs_queue.front();
            bfs_queue.pop();
            int found_vertex = um.first;
            int maximum_flow = um.second;

            if (found_vertex != target)
            {
                TR(edge_index, G[found_vertex])
                {
                    auto edge = edges[edge_index];

                    // Choose next vertex and calculate residual capacity
                    // based on whether it's a residual edge or a real edge
                    bool is_real_edge = (edge.from == found_vertex);
                    int next_vertex = is_real_edge ? edge.to : edge.from;
                    int residual_capacity = is_real_edge ? (edge.capacity - edge.flow) : edge.flow;

                    int residual_flow = min(maximum_flow, residual_capacity);
                    if (residual_flow > 0 && !HAS(edge_leading_to, next_vertex))
                    {
                        bfs_queue.push(PAIR(next_vertex, residual_flow));
                        edge_leading_to[next_vertex] = edge_index;
                    }
                }
            }
            else if (found_vertex == target)
            {
                // augment flow along the path source ----> target
                increase_in_flow = maximum_flow;
                int current_vertex = target;
                while (current_vertex != source)
                {
                    auto e = &edges[edge_leading_to[current_vertex]];
                    if (e->from == current_vertex)
                    {
                        // Revert flow along the residual edge
                        e->flow -= increase_in_flow;
                        current_vertex = e->to;
                    }
                    else
                    {
                        // Increment flow along the real edge
                        e->flow += increase_in_flow;
                        current_vertex = e->from;
                    }
                }
                break;
            }
        }

        if (increase_in_flow == 0)
            break;
        flow += increase_in_flow;
    }
    return flow;
}

int binary_search(const vi &values, int value, int i, int j)
{
    if (values[i] == value)
        return i;
    if (values[j] == value)
        return j;
    if (i == j || i == (j - 1))
        return -1;
    int mid = (i + j) / 2;
    if (values[mid] == value)
        return mid;
    if (values[mid] > value)
        return binary_search(values, value, i + 1, mid - 1);
    return binary_search(values, value, mid + 1, j - 1);
}

void append_slot(vii &slots, ii slot)
{
    if (slots.size() == 0 || slots[slots.size() - 1].second < slot.first)
    {
        slots.push_back(slot);
    }
    else if (slots[slots.size() - 1].second == slot.first)
    {
        slots[slots.size() - 1].second = slot.second;
    }
}

int main()
{
    int source = 0, target = 1;
    int case_no = 1;
    while (true)
    {
        vi empty;
        G.assign(505, empty);
        edges.clear();

        int n, m;
        scanf("%d %d", &n, &m);
        if (n == 0)
            break;

        int total_requirement = 0;
        typedef struct
        {
            int amount;
            int start;
            int end;
        } drinking_slot;
        vector<drinking_slot> drinking_slots;
        REP(i, 0, n)
        {
            int v, a, b;
            scanf("%d %d %d", &v, &a, &b);
            add_edge({source, monkey_index(i), v, 0});
            total_requirement += v;
            drinking_slots.push_back({v, a, b});
        }

        vi interval_markers;
        vi duplicate_interval_markers;
        TR(slot, drinking_slots)
        {
            duplicate_interval_markers.push_back(slot.start);
            duplicate_interval_markers.push_back(slot.end);
        }

        // Remove duplicates
        sort(ALL(duplicate_interval_markers));
        interval_markers.push_back(duplicate_interval_markers[0]);
        REP(i, 1, duplicate_interval_markers.size())
        {
            if (duplicate_interval_markers[i] == interval_markers[interval_markers.size() - 1])
                continue;
            interval_markers.push_back(duplicate_interval_markers[i]);
        }

        REP(i, 0, interval_markers.size() - 1)
        {
            add_edge({time_slot_index(i), target, m * (interval_markers[i + 1] - interval_markers[i]), 0});
        }

        REP(i, 0, drinking_slots.size())
        {
            auto slot = drinking_slots[i];
            int slot_start = binary_search(interval_markers, slot.start, 0, interval_markers.size() - 1);
            int slot_end = binary_search(interval_markers, slot.end, 0, interval_markers.size() - 1);
            REP(j, slot_start, slot_end)
            {
                add_edge({monkey_index(i), time_slot_index(j), interval_markers[j + 1] - interval_markers[j], 0});
            }
        }

        if (compute_max_flow(source, target) == total_requirement)
        {
            printf("Case %d: Yes\n", case_no);
            vvii slots(MAXN);
            REP(i, 0, interval_markers.size() - 1)
            {
                int interval_index = time_slot_index(i);
                int range = interval_markers[i + 1] - interval_markers[i];
                int next_start = 0;
                TR(edge_index, G[interval_index])
                {
                    auto edge = edges[edge_index];
                    if (edge.to == interval_index && edge.flow > 0)
                    {
                        int mnky = monkey(edge.from);
                        int next_end = (next_start + edge.flow) % range;

                        if (next_end > next_start)
                        {
                            append_slot(slots[mnky], PAIR(interval_markers[i] + next_start, interval_markers[i] + next_end));
                        }
                        else if (next_end == next_start)
                        {
                            append_slot(slots[mnky], PAIR(interval_markers[i], interval_markers[i + 1]));
                        }
                        else
                        {
                            if (next_end > 0)
                                append_slot(slots[mnky], PAIR(interval_markers[i], interval_markers[i] + next_end));

                            append_slot(slots[mnky], PAIR(interval_markers[i] + next_start, interval_markers[i + 1]));
                        }

                        next_start = next_end;
                    }
                }
            }

            REP(i, 0, n)
            {
                printf("%d", slots[i].size());
                TR(slot, slots[i])
                {
                    printf(" (%d,%d)", slot.first, slot.second);
                }
                printf("\n");
            }
        }
        else
        {
            printf("Case %d: No\n", case_no);
        }
        case_no++;
    }
    return 0;
}