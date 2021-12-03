struct point{
    int x, y;
};

struct vec{
    int x, y;
};

vec operator - (const point &A, const point &B){
    return vec{A.x - B.x, A.y - B.y};
}

int cross(vec A, vec B){
    return A.x*B.y - A.y*B.x;
}

int cross(point A, point B, point C){
    int val = A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y);
    if(val == 0)
        return 0; // coline
    if(val < 0)
        return 1; // clockwise
    return -1; //counter clockwise
}

vector <point> findConvexHull(vector <point> points){
    vector <point> convex;
    sort(points.begin(), points.end(), [](const point &A, const point &B){
        return (A.x == B.x)? (A.y < B.y): (A.x < B.x);
    });
    vector <point> Up, Down;
    point A = points[0], B = points.back();
    Up.push_back(A);
    Down.push_back(A);

    for(int i = 0; i < points.size(); i++){
        if(i == points.size()-1 || cross(A, points[i], B) > 0){
            while(Up.size() > 2 && cross(Up[Up.size()-2], Up[Up.size()-1], points[i]) <= 0)
                Up.pop_back();
            Up.push_back(points[i]);
        }
        if(i == points.size()-1 || cross(A, points[i], B) < 0){
            while(Down.size() > 2 && cross(Down[Down.size()-2], Down[Down.size()-1], points[i]) >= 0)
                Down.pop_back();
            Down.push_back(points[i]);
        }
    }
    for(int i = 0; i < Up.size(); i++)  convex.push_back(Up[i]);
    for(int i = Down.size()-2; i > 0; i--)  convex.push_back(Down[i]);
    return convex;
}

int dist(point A, point B){
    return (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y);
}

double findConvexDiameter(vector <point> convexHull){
    int n = convexHull.size();

    int is = 0, js = 0;
    for(int i = 1; i < n; i++){
        if(convexHull[i].y > convexHull[is].y)
            is = i;
        if(convexHull[js].y > convexHull[i].y)
            js = i;
    }

    int maxd = dist(convexHull[is], convexHull[js]);
    int i, maxi, j, maxj;
    i = maxi = is;
    j = maxj = js;
    do{
        int ni = (i+1)%n, nj = (j+1)%n;
        if(cross(convexHull[ni] - convexHull[i], convexHull[nj] - convexHull[j]) <= 0){
            j = nj;
        }else{
            i = ni;
        }
        int d = dist(convexHull[i], convexHull[j]);
        if(d > maxd){
            maxd = d;
            maxi = i;
            maxj = j;
        }
    }while(i != is || j != js);
    return sqrt(maxd);
}