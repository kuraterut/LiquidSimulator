#include <bits/stdc++.h>
#include "FIXED.hpp"

using namespace std;

constexpr std::array<pair<int, int>, 4> deltas{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};
mt19937 rnd(1337);

template<typename Type, int N, int M>
struct VectorField {
    array<Type, deltas.size()> v[N][M];
    Type &add(int x, int y, int dx, int dy, Type dv) {
        return get(x, y, dx, dy) += dv;
    }

    Type &get(int x, int y, int dx, int dy) {
        size_t i = ranges::find(deltas, pair(dx, dy)) - deltas.begin();
        assert(i < deltas.size());
        return v[x][y][i];
    }
};




template<typename Type>
struct ParticleParams {
    char type;
    Type cur_p;
    array<Type, deltas.size()> v;

    template<typename VType, typename PType, int N, int M>
    void swap_with(int x, int y, char** &field, VectorField<VType, N, M> velocity, PType p[N][M]) {
        swap(field[x][y], type);
        swap(p[x][y], cur_p);
        swap(velocity.v[x][y], v);
    }
};


template<typename PType, typename VType, typename VFType, int N, int M>
class Simulator{
	char** field;

	
	static constexpr size_t T = 1'000'000;
	PType g;

	PType rho[256];
	PType p[N][M]{}, old_p[N][M];

	VectorField<VType, N, M> velocity{};
	VectorField<VFType, N, M> velocity_flow{};

	int last_use[N][M]{};
	int UT = 0;

	int dirs[N][M]{};

	template<typename Type>
	tuple<Type, bool, pair<int, int>> propagate_flow(int x, int y, Type lim);

	template<typename Type>
	Type random01();

	void propagate_stop(int x, int y, bool force = false);

	template<typename Type>
	Type move_prob(int x, int y);


	template<typename Type>
	bool propagate_move(int x, int y, bool is_first);


public:
	void set_field(char** field){
		this->field = field;
	}

	void execute();


};