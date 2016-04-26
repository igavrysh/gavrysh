# gavrysh
mytestcourse
my notes for IDPHumanAssignment

1. IDPHumanBurnChild(human)
1.a if human if male IDPHumanBurnChild(human->_partner)
1.b CreateObject for child and retain it(nothing to do since it is already retained)

2 IDPHumanSetChild(human, child)
2.a.1 if human is mother add to array of childs, otherwise release it
2.a.2 add childs->_mother = human
2.a.1 if human is father add to array of childs, and retain it otherwise release it.
2.a.2 add childs->_father = human

3 IDPHumanRemoveChild(human, child) 
3.1 Human goes through all children and searches for child, if finds, goes into child and removes parent(father, mother link) 
	Releases it and starts shifting array
3.2 Human
3.2 IDPHumanRemoveParent()



IDPHuman *IDPHumanBurnChild(human) {
  if (!human) {
      return;
  }
  
  if (Male == IDPHumanGetGender) {
      return IDPHumanBurnChild(IDPHumanGetPartner(human));
  }
  
  IDPHuman *child = IDPObjectCreate(IDPHuman);
  IDPHumanSetChildStrongRef(human->_partner, child);
  IDPHumanSetChildStrongRef(human, child);
  IDPObjectRelease(child)
  
  return child;
}


#define IDPHumanRemoveAllChildren(IDPHuman *human) {\
	return IDPHumanRemoveChild(human, NULL); \\
\}

deallocate(human, child) {
    if (!human) {
        return;
    }
	

    IDPHumanReleaseChildStrongRef(human->_father, human);
    IDPHumanReleaseChildStrongRef(human->_mother, human);
    IDPHumanRemoveAllChildren(human, NULL);
}


IDPHumanReleaseChildStrongRef(human, child) {
    if (!human) { 
        return;
    }
    
    IDPHumanRemoveChild(human, child);
    IDPHumanSetChildStrongRef(human, NULL)
}


IDPHumanSetChildStrongRef(human, child) {
    if (!human) { 
        return;
    }
    
    if (male == IDPHumanGetGender(human)) {
    	child->_father = IDPHumanAddChild(human, child);
    } else {
    	child->_mother = IDPHumanAddChild(human, child);
    }	
}


IDPHuman* IDPHumanAddChild(human, child) {
    if (human || child) {
	return NULL;
	}

    for(uint8_t i = 0; i < kIDPHumanChildCount; i++) {
    	if (!human->_children[i]) {
	   human->_children[i] = IDPObjectRetain(child);
	   return human->_children[i];
	}
    }

    return NULL;    
}

IDPHuman* IDPHumanRemoveChild(human, child) {
    bool shiftChilds = false;
    for(uint8_t i = 0; i < kIDPHumanChildCount; i++) {
    	if (human->_children[i] == child || !child) {
	   
	   IDPObjectRelease(child);
	   shiftChilds = true;
	}
        if (shiftChilds && child) {
	   human->_children[i] = (i == kIDPHumanChildCount-1) ? NULL : human->_children[i+1];
	}
    }

    return NULL;
}
