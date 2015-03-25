ALTER TABLE Alias
	ADD CONSTRAINT Alias_PK PRIMARY KEY (Alias_id);
	
ALTER TABLE Criminals
	ADD CONSTRAINT Criminals_PK PRIMARY KEY (Criminal_id);
	
ALTER TABLE Crimes
	ADD CONSTRAINT Crimes_PK PRIMARY KEY (Crime_id);
	
ALTER TABLE Sentences
	ADD CONSTRAINT Sentences_PK PRIMARY KEY (Sentence_id);
	
ALTER TABLE Prob_officers
	ADD CONSTRAINT Prob_officers_PK PRIMARY KEY (Prob_id);
	
ALTER TABLE Crime_charges
	ADD CONSTRAINT Crime_charges_PK PRIMARY KEY (Charge_id);
	
ALTER TABLE Crime_officers
	ADD CONSTRAINT Crime_officers_PK PRIMARY KEY (Crime_id, Officer_id);

ALTER TABLE Officers
	ADD CONSTRAINT Officers_PK PRIMARY KEY (Officer_id);
	
ALTER TABLE Appeals
	ADD CONSTRAINT Appeals_PK PRIMARY KEY (Appeal_id);
	
ALTER TABLE Crime_codes
	ADD CONSTRAINT Crime_codes_PK PRIMARY KEY (Crime_code);

ALTER TABLE Alias
	ADD CONSTRAINT Alias_FK_Criminals FOREIGN KEY (Criminal_id) REFERENCES Criminals (Criminal_id);

ALTER TABLE Alias
	MODIFY (Criminal_id NOT NULL);
	
ALTER TABLE Criminals
	ADD CONSTRAINT V_status_CK CHECK (V_status IN('Y', 'N'));

ALTER TABLE Criminals
	ADD CONSTRAINT P_status_CK CHECK (P_status IN('Y', 'N'));	
	
ALTER TABLE Crimes
	ADD CONSTRAINT Crimes_FK_Criminals FOREIGN KEY (Criminal_id) REFERENCES Criminals (Criminal_id);
	
ALTER TABLE Crimes
	Modify (Criminal_id NOT NULL);
	
ALTER TABLE Crimes
	ADD CONSTRAINT Classification_CK CHECK (Classification IN ('F', 'M', 'O', 'U'));
	
ALTER TABLE Crimes
	ADD CONSTRAINT Crimes_Status_CK CHECK (Status IN ('CL', 'CA', 'IA'));
	
ALTER TABLE Sentences
	ADD CONSTRAINT Sentences_FK_Criminals FOREIGN KEY (Criminal_id) REFERENCES Criminals (Criminal_id);

ALTER TABLE Sentences
	Modify (Criminal_id NOT NULL);

ALTER TABLE Sentences
	ADD CONSTRAINT Sentences_FK_Prob FOREIGN KEY (Prob_id) REFERENCES Prob_officers (Prob_id);	
	
ALTER TABLE Sentences
	ADD CONSTRAINT Type_CK CHECK (Type IN ('J', 'H', 'P'));
	
ALTER TABLE Prob_officers
	ADD CONSTRAINT Prob_Status_CK CHECK (Status IN ('A', 'I'));
	
ALTER TABLE Crime_charges
	ADD CONSTRAINT Charges_FK_Crime FOREIGN KEY (Crime_id) REFERENCES Crimes (Crime_id);

ALTER TABLE Crime_charges
	Modify (Crime_id NOT NULL);
	
ALTER TABLE Crime_charges
	ADD CONSTRAINT Charges_FK_Codes FOREIGN KEY (Crime_code) REFERENCES Crime_codes (Crime_code);
	
ALTER TABLE Crime_charges
	Modify (Crime_code NOT NULL);
	
ALTER TABLE Crime_charges
	ADD CONSTRAINT Charge_Status_CK CHECK (Charge_status IN ('PD', 'GL', 'NG'));
	
ALTER TABLE Crime_officers
	ADD CONSTRAINT Officers_FK_Crimes FOREIGN KEY (Crime_id) REFERENCES Crimes (Crime_id);
	
ALTER TABLE Crime_officers
	Modify (Crime_id NOT NULL);

ALTER TABLE Crime_officers
	ADD CONSTRAINT Officers_FK_Officers FOREIGN KEY (Officer_id) REFERENCES Officers (Officer_id);
	
ALTER TABLE Crime_officers
	Modify (Officer_id NOT NULL);
	
ALTER TABLE Appeals
	ADD CONSTRAINT Appeals_FK_Crimes FOREIGN KEY (Crime_id) REFERENCES Crimes (Crime_id);
	
ALTER TABLE Appeals
	Modify (Crime_id NOT NULL);
	
ALTER TABLE Appeals
	ADD CONSTRAINT Appeals_Status_CK CHECK (Status IN ('P', 'A', 'D'));
	

	
