-- Create Conference table
CREATE TABLE Conference (
    Conference_ID INTEGER PRIMARY KEY,
    Name TEXT
);

-- Create Division table
CREATE TABLE Division (
    Division_ID INTEGER PRIMARY KEY,
    Name TEXT,
    Conference_ID INTEGER,
    FOREIGN KEY (Conference_ID) REFERENCES Conference(Conference_ID)
);

-- Create Team table
CREATE TABLE Team (
    Team_ID INTEGER PRIMARY KEY,
    Name TEXT,
    Mascot TEXT,
    City TEXT,
    State TEXT,
    Arena TEXT,
    Division_ID INTEGER,
    Coach_ID INTEGER,
    FOREIGN KEY (Division_ID) REFERENCES Division(Division_ID),
    FOREIGN KEY (Coach_ID) REFERENCES Coach(Coach_ID)
);

-- Create Player table
CREATE TABLE Player (
    Player_ID INTEGER PRIMARY KEY,
    First_Name TEXT,
    Last_Name TEXT,
    Number INTEGER,
    Team_ID INTEGER,
    FOREIGN KEY (Team_ID) REFERENCES Team(Team_ID)
);

-- Create Coach table
CREATE TABLE Coach (
    Coach_ID INTEGER PRIMARY KEY,
    Name TEXT,
    Team_ID INTEGER,
    FOREIGN KEY (Team_ID) REFERENCES Team(Team_ID)
);

-- Create Game table
CREATE TABLE Game (
    Game_ID INTEGER PRIMARY KEY,
    Date_Time TEXT,
    Home_Team_ID INTEGER,
    Away_Team_ID INTEGER,
    Home_Team_Score INTEGER,
    Away_Team_Score INTEGER,
    FOREIGN KEY (Home_Team_ID) REFERENCES Team(Team_ID),
    FOREIGN KEY (Away_Team_ID) REFERENCES Team(Team_ID)
);
