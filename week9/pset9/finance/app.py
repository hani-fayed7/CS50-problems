import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

#TODO
@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Initializing needed variables
    stocks = []
    remaining_cash = 10000.00
    total_cash = 0.00
    total_stocks_prices = 0.00

    # Loop through each stock and update the variables
    bought_stocks_row = db.execute("SELECT * FROM bought_stocks WHERE user_id = ?", session["user_id"])
    for row in bought_stocks_row:
        symbol = db.execute("SELECT symbol FROM bought_stocks WHERE user_id = ?", session["user_id"])
        name = db.execute("SELECT name FROM bought_stocks WHERE user_id = ?", session["user_id"])
        shares = db.execute("SELECT shares FROM bought_stocks WHERE user_id = ?", session["user_id"])
        price = db.execute("SELECT price FROM bought_stocks WHERE user_id = ?", session["user_id"])
        total = db.execute("SELECT total FROM bought_stocks WHERE user_id = ?", session["user_id"])

        stock_information = {"symbol":symbol, "name":name, "shares":shares, "price": price, "total": total}
        total_stocks_prices += total
        remaining_cash -= total

        stocks.append(stock_information)

    total_cash = total_stocks_prices + remaining_cash

    return render_template("portfolio.html", stocks=stocks, remaining=str(remaining_cash), total=str(total_cash))


#TODO
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        shares = request.form.get("shares")

        # Ensure shares was submitted
        if not shares:
            return apology("missing shares", 400)

        stock = lookup(request.form.get("symbol"))

        # Ensure symbol is valid
        if stock == None:
            return apology("invalid symbol", 400)

        symbol = stock["symbol"]
        name = stock["name"]
        price = stock["price"]

        total = shares * price

        # Get users cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # Ensure that the user has enough cash
        if cash < total:
            return apology("can't afford", 400)

        id = db.execute("SELECT id FROM users WHERE id = ?", session["user_id"])
        time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Purchase stock
        db.execute("INSERT INTO bought_stocks (user_id, symbol, name, shares, price, total, time) VALUES(?, ?, ?, ?, ?, ?, ?)", id, symbol, name, shares, price, total, time)

        # Update cash
        remaining_cash = cash - total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", remaining_cash, session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


#TODO
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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

#TODO
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        quoted = lookup(request.form.get("symbol"))

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        # Ensure symbol is valid
        elif quoted == None:
            return apology("invalid symbol", 400)

        # Lookup is successful, go to quoted
        return render_template("quoted.html", quoted=quoted)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

#TODO:
#FIXME
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure that the confirmation password is correct
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords must match", 400)

        # Ensure username is unique
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) == 1:
            return apology("username exists", 400)

        # Add user to database
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        # Remember which user has logged in
        session["user_id"] = users[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

#TODO
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    boughtSymbols = db.execute("SELECT symbol FROM bought_stocks WHERE user_id = ?", session["user_id"])
    bought = []
    for row in boughtSymbols:
        bought.append(row)


    if request.method == "POST":

        # Ensure symbol was sybmitted
        if not request.form.get("symbol"):
            return apology("missing symbol", 400)

        # Ensure shares was submitted
        if not request.form.get("shares"):
            return apology("missing shares", 400)


        symbol_current_price = db.execute("SELECT price FROM bought_stocks WHERE user_id = ? AND symbol = ?", session["user_id"], request.form.get("symbol"))
        get_bought_shares = db.execute("SELECT shares FROM bought_stocks WHERE user_id = ? AND symbol = ?", session["user_id"], request.form.get("symbol"))

        # Ensure that the number of shares isn't bigger than the shares the user bought
        if request.form.get("shares") > get_bought_shares:
            return apology("too many shares", 400)

        # Sell the specified number of shares of stock
        sell = get_bought_shares * symbol_current_price


        # Update the user's cash
        updated_cash = db.execute("UPDATE users SET cash = ? WHERE id = ?", sell, session["user_id"])

        # Update the sold_stocks database
        #TODO: review history and home page; update the shares and the total
        name = db.execute("SELECT name FROM bought_stocks WHERE user_id = ? and symbol = ?", session["usser_id"], request.form.get("symbol"))

        db.execute("INSERT INTO sold_stocks (symbol, name , shares, price, total, time) VALUES (?, ?, ?, ?, ?, ?)", request.form.get("symbol"), name, request.form.get("shares"), )

        # Redirect user to home page
        return redirect("/")

    else:
        return render.template("sell.html", bought=bought)


