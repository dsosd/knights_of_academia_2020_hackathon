<nav>
    <h1 id="brand">the-knights</h1>

    <ul id="nav-icons">
        <li>
            <a href="https://github.com/SagnikPradhan/the-knights">
                <img alt="github-icon" src="https://img.icons8.com/nolan/64/github.png"/>
            </a>
        </li>
    </ul>
</nav>

<style>
    @import url('https://fonts.googleapis.com/css?family=Quicksand&display=swap');

    nav {
        z-index: 50;

        height: auto;
        width: -webkit-fill-available;
        background: #000000;

        display: grid;
        grid-template-areas: "B L";

        box-shadow: 0 0 20px black;
    }

    nav h1#brand {
        grid-template: "B";

        margin: 20px 40px;

        display: flex;
        align-items: center;

        color: #921eff;
        font-size: 32px;
        font-family: 'Quicksand', sans-serif;
    }

    ul#nav-icons {
        grid-template: "L";

        margin: 15px 40px;
        padding: 0px;

        list-style: none;

        display: flex;
        flex-direction: row-reverse;
        align-items: center;
    }

    ul#nav-icons li a img {
        height: 40px;
        width: auto;
    }
</style>