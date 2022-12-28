#include <SDL.h>
#include "rule_manager.h"
#include "port.h"
#include "consts.h"
static void rule__check(struct Rule *_) {

    switch (_->condition_id)
    {
    case ConditionType_and:
        _->state = wire_manager.getPort(&wire_manager,_->port1_id,PortType_output)->isActive && wire_manager.getPort(&wire_manager,_->port2_id,PortType_output)->isActive;
        break;
    case ConditionType_or:
        _->state = wire_manager.getPort(&wire_manager,_->port1_id,PortType_output)->isActive || wire_manager.getPort(&wire_manager,_->port2_id,PortType_output)->isActive;
        break;
    case ConditionType_not:
        _->state = !wire_manager.getPort(&wire_manager,_->port1_id,PortType_output)->isActive;
    break;
    }

    wire_manager.getPort(&wire_manager,_->output_id,PortType_input)->isActive = _->state;

}




static struct Rule rule__new(int p1_id , int p2_id ,int output_id, int condition) {

    struct Rule _;

    _.id = random();
    _.check = &rule__check; 
    
    _.port1_id = p1_id;
    _.port2_id = p2_id;
    _.output_id = output_id;
    _.condition_id = condition;


    return _;
}
const struct RuleClass Rule = {.new = rule__new};
