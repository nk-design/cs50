import sqlite3
import os

from flask import Flask, g, redirect, render_template, request, url_for

from init_db import DB_PATH, init_db

app = Flask(__name__)


def get_db():
    if "db" not in g:
        g.db = sqlite3.connect(DB_PATH)
        g.db.row_factory = sqlite3.Row
    return g.db


@app.teardown_appcontext
def close_db(exception=None):
    db = g.pop("db", None)
    if db is not None:
        db.close()


@app.route("/")
def index():
    db = get_db()
    rows = db.execute(
        "SELECT id, name, month, day FROM birthdays ORDER BY month, day"
    ).fetchall()
    return render_template("index.html", birthdays=rows)


@app.route("/add", methods=["POST"])
def add():
    name = request.form.get("name", "").strip()
    month = request.form.get("month", "")
    day = request.form.get("day", "")

    if name and month.isdigit() and day.isdigit():
        month = int(month)
        day = int(day)
        if 1 <= month <= 12 and 1 <= day <= 31:
            db = get_db()
            db.execute(
                "INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)",
                (name, month, day),
            )
            db.commit()

    return redirect(url_for("index"))


@app.route("/delete/<int:birthday_id>", methods=["POST"])
def delete(birthday_id):
    db = get_db()
    db.execute("DELETE FROM birthdays WHERE id = ?", (birthday_id,))
    db.commit()
    return redirect(url_for("index"))


if __name__ == "__main__":
    if not os.path.exists(DB_PATH):
        init_db()
    app.run(debug=True)
