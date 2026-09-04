-- List the names of all people who starred in "Forrest Gump"
SELECT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.title = 'Forrest Gump';

-- List the titles of all movies Kevin Bacon starred in, in any order
SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Kevin Bacon';

-- List titles and ratings of movies rated 8.0 or higher, sorted from highest to lowest
SELECT movies.title, ratings.rating
FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >= 8.0
ORDER BY ratings.rating DESC;

-- List the names of directors, along with the titles of movies they directed
SELECT people.name, movies.title
FROM people
JOIN directors ON people.id = directors.person_id
JOIN movies ON directors.movie_id = movies.id
ORDER BY people.name;

-- Find movies that share at least one star with "Forrest Gump", excluding Forrest Gump itself
SELECT DISTINCT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE stars.person_id IN (
    SELECT stars.person_id
    FROM stars
    JOIN movies ON stars.movie_id = movies.id
    WHERE movies.title = 'Forrest Gump'
)
AND movies.title != 'Forrest Gump';
