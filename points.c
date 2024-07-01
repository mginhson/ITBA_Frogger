#include <stdio.h>

void logic_pts (){
    static int pts;
    int forward = frog_move_forward();
    int backward = frog_move_backward ();
    int leaf = frog_reach_leaf ();
    int fly = frog_catch_fly ();
    int extra_frog = frog_cactch_extra_frog ();
    int new_level = frog_passes_level ();
    if (forward){
        pts++;
    }
    if (backward){
        pts--;
    }
    if (leaf && !fly && !extra_frog){
        pts += 5;
    }
    if (fly && leaf && !extra_frog){
        pts += 10;
    }
    if (extra_frog && leaf && !fly){
        pts +=10;
    }
    if (leaf && fly && extra_frog){
        pts +=20;
    }
    if (new_level){
        pts += 25;
    }
}