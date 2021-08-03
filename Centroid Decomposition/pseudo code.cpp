//pseudo Code for Centroid Decomposition

int centroid;
int mark[size];

solve(v){
	int n = dfs_size(v,-1);
	dfs_centroid(v,-1);
	int c = centroid;
	mark[c] = true;
	calculate(c); // function to carry out task
	for(int u:g[c])
		if(!mark[u])
			solve(u);
}

int dfs_size(x,p){
	if(mark[x]) return 0;
	int s = 1;
	for(y : g[x])
		if(y != p )
			s += dfs_size(y,x)
	return s
}

int dfs_centroid(x,p){
	if(mark[x]) return 0;
	int s = 1;
	bool ok = true;
	for(y : g[x]){
		if(y != p){
			sz = dfs_centroid(y,x)
			if(sz>n/2)
				ok = false
			s += sz;
		}
	}
	if(s < n/2)
		ok = false;
	if(ok == true)
		centroid  = x;
	return s;
}
