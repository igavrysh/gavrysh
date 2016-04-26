# gavrysh

void IDPHumanChildAdd(human, child) {
	IDPHumanSetChildWithNewValue(human, NULL, child);
	IDPHumanSetChildWithNewValue(partner, NULL, child);
	
	IDPHumanSetParent(child, human, human);
	IDPHumanSetParent(child, parent, parent);
}

void IDPHumanRemoveChild(IDPHuman human) {
	IDPHumanSetChildWithNewValue(human, child, NULL);
	IDPHumanSetChildWithNewValue(partner, child, NULL);
	
	IDPHumanSetParent(child, human, NULL);
	IDPHumanSetParent(child, partner, NULL);
}

void IDPHumanRemoveAllChildren(IDPHuman human) {
	for (size_t index = 0; index < IDPHumanGetChildrenCount(human); index++) {
		IDPHumanRemoveChild(IDPHumanGetChildByIndex(human, index));
	}
}

void IDPHumanSetChildWithNewValue(human, child, newChild) {
	
	if (!child) {
		IDPHumanSetChildAtIndex(human, child, IDPGetCount());
	} else {
		index = IDPHumanGetIndexOfChild(human, child);
		IDPHumanSetChildAtIndex(human, NULL, index);
	}
}

void IDPHumanSetParent(human, parent, newParent) {
	if (IDPHumanMale == GetGender(parent)) {
		human->_father = newParent;
	} else if (IDPHumanFemale == GetGender(parent)){
		human->_mother = newParent;
	}
}


void IDPHumanSetChildAtIndex(human, childr, index) {
	
}

size_t IDPHumanGetIndexOfChild(human, child) {
	
}

