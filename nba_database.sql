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

-- Insert into Conference table
INSERT INTO Conference (Name) VALUES ('Eastern');
INSERT INTO Conference (Name) VALUES ('Western');

-- Insert into Division table
INSERT INTO Division (Name, Conference_ID) VALUES ('Atlantic', 1);
INSERT INTO Division (Name, Conference_ID) VALUES ('Central', 1);
INSERT INTO Division (Name, Conference_ID) VALUES ('Southeast', 1);
INSERT INTO Division (Name, Conference_ID) VALUES ('Northwest', 2);
INSERT INTO Division (Name, Conference_ID) VALUES ('Pacific', 2);
INSERT INTO Division (Name, Conference_ID) VALUES ('Southwest', 2);

-- Insert into Team table
INSERT INTO Team (Name, Mascot, City, State, Arena, Division_ID, Coach_ID) VALUES ('Boston Celtics', 'Leprechaun', 'Boston', 'MA', 'TD Garden', 1, 1);
INSERT INTO Team (Name, Mascot, City, State, Arena, Division_ID, Coach_ID) VALUES ('Los Angeles Lakers', 'Laker', 'Los Angeles', 'CA', 'Staples Center', 5, 2);

-- Insert sample data into Coach table
INSERT INTO Coach (Name, Team_ID) VALUES ('Brad Stevens', 1);
INSERT INTO Coach (Name, Team_ID) VALUES ('Frank Vogel', 2);

-- Insert into Player table
INSERT INTO Player (First_Name, Last_Name, Number, Team_ID) VALUES ('Jayson', 'Tatum', 0, 1);
INSERT INTO Player (First_Name, Last_Name, Number, Team_ID) VALUES ('LeBron', 'James', 23, 2);

-- Insert into Game table
INSERT INTO Game (Date_Time, Home_Team_ID, Away_Team_ID, Home_Team_Score, Away_Team_Score) VALUES ('2024-02-28 20:00:00', 1, 2, 112, 105);
