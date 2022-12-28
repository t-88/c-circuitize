#pragma once
#include <SDL.h>
#include "port.h"
#include "consts.h"

struct Rule {
    int port1_id,port2_id,output_id;
    int id, state;
    int condition_id;
    


    void (*check)(struct Rule *_);
};
extern const struct RuleClass {
    struct Rule (*new)(int,int,int,int);
} Rule;


struct RuleManager {
    int** port_states; //'[[ id , rule count, rule , ...]]'
    
    struct Rule* rules;
    int rule_count;

    void (*addRule)(struct RuleManager *_,int p1_id , int p2_id,int output_id,int condition);
    void (*getRuleByID)(struct RuleManager *_,int rule_id);
    void (*update)(struct RuleManager *_);
};

extern const struct RuleManagerClass {
    struct RuleManager (*new)();
} RuleManager;