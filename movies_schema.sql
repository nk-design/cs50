CREATE TABLE people (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    birth INTEGER
);

CREATE TABLE movies (
    id INTEGER PRIMARY KEY,
    title TEXT NOT NULL,
    year INTEGER,
    genre TEXT
);

CREATE TABLE stars (
    movie_id INTEGER,
    person_id INTEGER,
    FOREIGN KEY (movie_id) REFERENCES movies(id),
    FOREIGN KEY (person_id) REFERENCES people(id)
);

CREATE TABLE directors (
    movie_id INTEGER,
    person_id INTEGER,
    FOREIGN KEY (movie_id) REFERENCES movies(id),
    FOREIGN KEY (person_id) REFERENCES people(id)
);

CREATE TABLE ratings (
    movie_id INTEGER,
    rating REAL,
    FOREIGN KEY (movie_id) REFERENCES movies(id)
);
