#include <vector>
using std::vector;


const vector<vector<int>> EASY = {
    {
        1  , 2  , 3  , 4  ,
        5  , 6  , 12 , 7  ,
        9  , 10 , 0  , 15 ,
        13 , 14 , 8  , 11
    }
};

const vector<vector<int>> NORMAL = {
    {
        1  , 6  , 3  , 4  ,
        5  , 0  , 2  , 11 ,
        9  , 10 , 14 , 7  ,
        13 , 15 , 12 , 8
    }
};

const vector<vector<int>> HARD = {
    {
        6  , 5  , 11 , 4 ,
        10 , 13 , 2  , 1 ,
        9  , 15 , 7  , 3 ,
        14 , 12 , 8  , 0
    }
};

const vector<vector<int>> IMPOSSIBLE = {
    {
        0  , 12 , 11 , 13,
        15 , 14 , 10 , 9 ,
        3  , 7  , 6  , 2 ,
        4  , 8  , 5  , 1
    }
};

const vector<int> DEMO = {
    1, 2, 7, 3, 5, 6, 4, 0, 9, 10, 11, 8, 13, 14, 15, 12
};
