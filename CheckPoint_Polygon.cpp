#include<iostream>
using namespace std;

struct Point {
   int x, y;
};

struct line {
   Point p1, p2;
};

bool onLine(line l1, Point p) {        
   if(p.x <= max(l1.p1.x, l1.p2.x) && p.x <= min(l1.p1.x, l1.p2.x) &&
      (p.y <= max(l1.p1.y, l1.p2.y) && p.y <= min(l1.p1.y, l1.p2.y)))
         return true;

   return false;
}

int direction(Point a, Point b, Point c) {
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;           
   else if(val < 0)
      return 2;          
      return 1;          
}

bool checkIntersect(line l1, line l2) {
  
   int dir1 = direction(l1.p1, l1.p2, l2.p1);
   int dir2 = direction(l1.p1, l1.p2, l2.p2);
   int dir3 = direction(l2.p1, l2.p2, l1.p1);
   int dir4 = direction(l2.p1, l2.p2, l1.p2);

   if(dir1 != dir2 && dir3 != dir4)
      return true;           
   if(dir1==0 && onLine(l1, l2.p1))        
      return true;
   if(dir2==0 && onLine(l1, l2.p2))         
      return true;
   if(dir3==0 && onLine(l2, l1.p1))       
      return true;
   if(dir4==0 && onLine(l2, l1.p2)) 
      return true;
   return false;
}

bool checkPoint(Point poly[], int n, Point p) {
   if(n < 3)
      return false;                  
   line inFinite = {p, {9999, p.y}};   
   int count = 0;
   int i = 0;
   do {
      line side = {poly[i], poly[(i+1)%n]};    
      if(checkIntersect(side, inFinite)) {          
         if(direction(side.p1, p, side.p2) == 0)
            return onLine(side, p);
         count++;
      }
      i = (i+1)%n;
   } while(i != 0);
      return count&1;           
}

int main() {
   
   Point polygon[] = {{1,0}, {8, 3}, {8, 8}, {1, 5}};
   Point p = {3, 5};
   int n = 4;

   if(checkPoint(polygon, n, p))
      cout << "True";
   else
      cout << "False";
   return 0;
}