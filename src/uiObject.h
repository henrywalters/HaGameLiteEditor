//
// Created by henry on 12/29/22.
//

#ifndef HAGAMELITE_UIOBJECT_H
#define HAGAMELITE_UIOBJECT_H

#include "hagame/core/object.h"

class UIObject : public hg::Object {

public:
    virtual void update(double dt) {}
protected:
    [[nodiscard]] std::string toString() const override {
        return "UIObject<" + std::to_string(id()) + ">";
    }
};

#endif //HAGAMELITE_UIOBJECT_H
