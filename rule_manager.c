#include <SDL.h>
#include "rule_manager.h"
#include "port.h"
#include "consts.h"


static void rule_manger__add_rule(struct RuleManager *_,int p1_id , int p2_id,int output_id,int condition) {
    _->rule_count++;
    _->rules = realloc(_->rules,_->rule_count * sizeof(struct Rule));
    _->rules[_->rule_count - 1] = Rule.new(p1_id,p2_id,output_id,condition);

}
static void rule_manger__get_rule_by_id(struct RuleManager *_,int rule_id) {

}
static void rule_manger__update(struct RuleManager *_) {
    for (size_t i = 0; i < _->rule_count; i++){
        _->rules[i].check(&_->rules[i]);
    }
}




static struct RuleManager rule_manger__new() {
    struct RuleManager _;

    _.update = &rule_manger__update; 
    _.getRuleByID = &rule_manger__get_rule_by_id; 
    _.addRule = &rule_manger__add_rule; 

    _.rules = malloc(0);
    _.rule_count = 0;

    return _;
}
const struct RuleManagerClass RuleManager = {.new = rule_manger__new};
