/*
2126. Destroying Asteroids
You are given an integer mass, which represents the original mass of a planet. You are further given an integer array asteroids, where asteroids[i] is the mass of the ith asteroid.

You can arrange for the planet to collide with the asteroids in any arbitrary order. If the mass of the planet is greater than or equal to the mass of the asteroid, the asteroid is destroyed and the planet gains the mass of the asteroid. Otherwise, the planet is destroyed.

Return true if all asteroids can be destroyed. Otherwise, return false.

 

Example 1:

Input: mass = 10, asteroids = [3,9,19,5,21]
Output: true
Explanation: One way to order the asteroids is [9,19,5,3,21]:
- The planet collides with the asteroid with a mass of 9. New planet mass: 10 + 9 = 19
- The planet collides with the asteroid with a mass of 19. New planet mass: 19 + 19 = 38
- The planet collides with the asteroid with a mass of 5. New planet mass: 38 + 5 = 43
- The planet collides with the asteroid with a mass of 3. New planet mass: 43 + 3 = 46
- The planet collides with the asteroid with a mass of 21. New planet mass: 46 + 21 = 67
All asteroids are destroyed.
Example 2:

Input: mass = 5, asteroids = [4,9,23,4]
Output: false
Explanation: 
The planet cannot ever gain enough mass to destroy the asteroid with a mass of 23.
After the planet destroys the other asteroids, it will have a mass of 5 + 4 + 9 + 4 = 22.
This is less than 23, so a collision would not destroy the last asteroid.
 

Constraints:

1 <= mass <= 105
1 <= asteroids.length <= 105
1 <= asteroids[i] <= 105
*/
unsigned freq[100001]={0};
class Solution {
public:
    static bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        unsigned xmax=0, xmin=1e5;
        for(unsigned x: asteroids){
            freq[x]++;
            xmin=min(xmin, x);
            xmax=max(xmax, x);
        }
        long long planet=mass;// careful for overflow
        for(int x=xmin; x<=xmax; x++){
            if (freq[x]==0) continue;
            if (x>planet) {
                memset(freq+x, 0, (xmax-x+1)*sizeof(unsigned));
                return 0;
            }
            planet+=(long long)x*freq[x];
            freq[x]=0;
        }
        return 1;
    }
};
auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();