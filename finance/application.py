import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""



    # Select data from databases
    rows = db.execute("SELECT * FROM portfolios WHERE id = :user_id", user_id = session["user_id"])
    users = db.execute("SELECT * FROM users WHERE id = :user_id", user_id = session["user_id"])
    cash = float(users[0]["cash"])
    cash = "${:,.2f}".format(cash)

    total_sum = float(users[0]["cash"])

    #Update values for price & total w/ lookup
    for row in rows:

        price = lookup(row["symbol"])["price"]
        row["price"] = "${:,.2f}".format(price)

        cost = row["shares"]*price
        row["total"] = "${:,.2f}".format(cost)

        total_sum = total_sum + cost

    #format to display
    total = "${:,.2f}".format(total_sum)

    #render index
    return render_template("index.html", rows=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        #Get symbol & # shares from user, check for errors
        symbol = request.form.get("symbol")
        if not symbol or lookup(symbol) == None:
            return render_template("apology.html", message = "Invalid stock symbol")

        shares = request.form.get("shares")

        for n in (shares):
            if n == ".":
                return render_template("apology.html", message = "Please enter an integer")

        if not shares or int(shares) < 0:
            return render_template("apology.html", message = "Please enter valid number of shares")

        #Update cash for user after purchase
        row = db.execute("SELECT * FROM users WHERE id = :user_id", user_id = session["user_id"])
        cash = float(row[0]["cash"])
        price = float(lookup(symbol)["price"]) * int(shares)

        #error if not enough cash
        if cash < price:
            return render_template("apology.html", message = "Not enough cash, son!")

        #DB to store history of buys (and sells)
        db.execute("INSERT INTO buy (id, flow, symbol, name, price, shares, total, time) VALUES (:user_id, :flow, :symbol, :name, :price, :shares, :total, CURRENT_TIMESTAMP )", user_id = session["user_id"], flow = 'BUY', symbol = lookup(symbol)["symbol"], name = lookup(symbol)["name"], price = lookup(symbol)["price"], shares = shares, total = price )

        #Check if symbol in portfolio & update database
        p_shares = db.execute("SELECT * FROM portfolios WHERE id = :user_id AND symbol = :symbol", user_id = session["user_id"], symbol = lookup(symbol)["symbol"])
        if len(p_shares) == 1:
            new_shares = p_shares[0]['shares'] + int(shares)
            db.execute("UPDATE portfolios set shares = :new_shares WHERE id = :user_id AND symbol = :symbol", new_shares = new_shares, user_id = session["user_id"], symbol = lookup(symbol)["symbol"] )
        else:
            db.execute("INSERT INTO portfolios (id, symbol, name, price, shares, total) VALUES (:user_id, :symbol, :name, :price, :shares, :total)", user_id = session["user_id"], symbol = lookup(symbol)["symbol"], name = lookup(symbol)["name"], price = lookup(symbol)["price"], shares = shares, total = price)

        # Update available cash in user table
        new_cash  = cash - price
        db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash = new_cash, user_id = session["user_id"])

        return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * FROM buy WHERE id = :user_id", user_id = session["user_id"])
    for row in rows:
        price = row["price"]
        row["price"] = "${:,.2f}".format(price)

    return render_template("history.html", rows=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if lookup(symbol) == None:
            return render_template("apology.html", message = "Invalid stock symbol")
        else:
            stock_dict= lookup(symbol)
            return render_template("quoted.html", name = stock_dict["name"], price = "${:,.2f}".format(stock_dict["price"]), symbol = stock_dict["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    else:
        #Get username input
        username = request.form.get("username")
        if not username:
            return render_template("apology.html", message="You must provide a username")

       #check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) == 1:
            return render_template("apology.html", message="Sorry, homie, that username already exists")

        #Get password input & check confirmation
        password = request.form.get("password")
        if not password:
            return render_template("apology.html", message = "You must provide a password")
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return render_template("apology.html", message = "Please re-enter your password")
        if password != confirmation:
            return render_template("apology.html", message = "Passwords do not match")

        #Generate Hash Password
        hashed = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashed)", username=username, hashed= hashed)

        #Improvement idea: display a message to say you registered successfully (back burner)
        return render_template("login.html", message = "Congrats!")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    users = db.execute("SELECT * FROM users WHERE id = :user_id", user_id = session["user_id"])

    if request.method == "GET":
        rows = db.execute("SELECT * FROM portfolios WHERE id = :user_id", user_id = session["user_id"])
        return render_template("sell.html",rows=rows)

    else:
        rows = db.execute("SELECT * FROM portfolios WHERE id = :user_id AND symbol = :symbol", user_id = session["user_id"], symbol = request.form.get("symbol"))

        for n in (request.form.get("shares")):
            if n == ".":
                return render_template("apology.html", message = "Please enter an integer")

        if rows[0]["shares"] < int(request.form.get("shares")):
            return render_template("apology.html", message = "Invalid number of shares selected!")

        elif len(rows) !=1:
            return render_template("apology.html", message = "You don't own that stock!")

        else:
            new_shares = rows[0]["shares"] - int(request.form.get("shares"))
            db.execute("UPDATE portfolios set shares = :new_shares WHERE id = :user_id AND symbol = :symbol", new_shares = new_shares, user_id = session["user_id"], symbol = lookup(request.form.get("symbol"))["symbol"] )

            cash = float(users[0]["cash"])
            price = int(request.form.get("shares")) * float(lookup(request.form.get("symbol"))["price"])
            new_cash = cash + price
            db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash = new_cash, user_id = session["user_id"])

            #left to do, update BUY table as a SELL
            db.execute("INSERT INTO buy (id, flow, symbol, name, price, shares, total, time) VALUES (:user_id, :flow, :symbol, :name, :price, :shares, :total, CURRENT_TIMESTAMP )", user_id = session["user_id"], flow = 'SELL', symbol = lookup(request.form.get("symbol"))["symbol"], name = lookup(request.form.get("symbol"))["name"], price = lookup(request.form.get("symbol"))["price"], shares = request.form.get("shares"), total = price )

            return redirect("/")

    # check error case of not owning stock (TODO)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)


