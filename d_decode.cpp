#include <cstdio>

using namespace std;

unsigned int e = 47;

void h(FILE *out) {
	int a[6] = {0, 1, 2, 3, 4, 5};
	for(int b = 1; 6 > b; b++) {
		e *= 53;
		e %= 1000000009;
		int k = e % (b+1), d = a[b];
		a[b] = a[k];
		a[k] = d;
        fprintf(out, "e: %d k: %d b: %d\n", e, k, b);
	}
	for(int i = 0; i < 6; i++)
		fprintf(out, "%d%c", a[i], (i == 5 ? '\n' : ' '));
}

int main() {
    /*
	FILE *out = fopen("d_decode.txt", "w");
	fprintf(out, "Initial state of a[] = 0 1 2 3 4 5\n");
    fprintf(out, "a[] of iteration initial for f():\n");
    h(out);
    fprintf(out, "a[] of iteration initial for g():\n");
    h(out);
    e=47;
	for(int i = 0; i < 472*2; i++) {
		for(int j = 0; j < 2; j++) {
			fprintf(out, "a[] of iteration %d for f():\n", i+1);
			h(out);
			fprintf(out, "a[] of iteration %d for g():\n", i+1);
			h(out);
		}
	}
	fclose(out);*/
    
    for(int i=0;i<3;++i){
        char q;
        double c;
        scanf("%c", &q);
        
        if(q=='Q'){
            scanf("%lf",&c);
            getchar();
        }
    }
	return 0;
}
/*
(function() {
    function h() {
        for (var a = [0, 1, 2, 3, 4, 5], b = 1; 6 > b; b++) {
            e*=53;
            e%=1000000009;
            var k = e%(b + 1), d = a[b];
            a[b] = a[k];
            a[k] = d
        }
        return a
    }
    function l() {
        for (var b = [[50, 50],
                      [50, 150], [50, 250], [150, 50], [150, 150], [150, 250]], 
                d = [[250, 50], [250, 150], [250, 250], [450, 50], [450, 150], [450, 250]],
                e = "#ff0000 #00ff00 #0000ff #ffff00 #ff8800 #ff00ff".split(" "),
                f = h(), g = h(),
                c = 0; 6 > c; c++)
            a.fillStyle = e[f[c]], a.fillRect(b[c][0], b[c][1], 50, 50);
        for (c = 0; 6 > c; c++)
            a.fillStyle = e[g[c]], a.fillRect(d[c][0], d[c][1], 100, 50)
            }
    var d = 0, e = 47
    l();
    e = 47
})();
*/

