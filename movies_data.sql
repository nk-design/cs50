INSERT INTO people (id, name, birth) VALUES
    (1, 'Tom Hanks', 1956),
    (2, 'Robin Wright', 1966),
    (3, 'Kevin Bacon', 1958),
    (4, 'Meryl Streep', 1949),
    (5, 'Christopher Nolan', 1970),
    (6, 'Robert Zemeckis', 1951),
    (7, 'Leonardo DiCaprio', 1974),
    (8, 'Elliot Page', 1987);

INSERT INTO movies (id, title, year, genre) VALUES
    (101, 'Forrest Gump', 1994, 'Drama'),
    (102, 'Inception', 2010, 'Sci-Fi'),
    (103, 'The Post', 2017, 'Drama');

INSERT INTO stars (movie_id, person_id) VALUES
    (101, 1), (101, 2), (101, 3),
    (102, 7), (102, 8),
    (103, 4), (103, 1);

INSERT INTO directors (movie_id, person_id) VALUES
    (101, 6),
    (102, 5),
    (103, 6);

INSERT INTO ratings (movie_id, rating) VALUES
    (101, 8.8),
    (102, 8.8),
    (103, 7.2);
