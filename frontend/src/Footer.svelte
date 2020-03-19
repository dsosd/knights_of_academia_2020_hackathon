<footer>
    <h2 id="label">Credits</h2>

    <ul id="credits-list">
        <li>
            <a href="https://icons8.com/icons">
                <img alt="icons8" src="https://img.icons8.com/nolan/64/icons8-new-logo.png"/>
            </a>
        </li>
    </ul>
</footer>

<style>
    @import url('https://fonts.googleapis.com/css?family=Nunito&display=swap');

    footer {
        z-index: 50;

        padding: 20px 40px;

        display: flex;
        flex-direction: row;
        align-items: center;

        background: #000000;
        box-shadow: 0 0 20px black;
    }

    footer h2#label {
        font-size: 22px;
        padding: 0 10px 0 0;
    }

    footer ul#credits-list {
        list-style: none;
        margin: 0px;
        padding: 0px;

        flex-grow: 100;

        display: inline-flex;
        flex-direction: row-reverse;
        align-items: center;
    }

    footer ul#credits-list li img {
        height: 40px;
        width: auto;
    }
</style>
