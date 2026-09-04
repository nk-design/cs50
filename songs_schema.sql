CREATE TABLE songs (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    artist TEXT NOT NULL,
    danceability REAL,
    energy REAL,
    valence REAL,
    tempo REAL,
    duration_ms INTEGER
);
