<main>
    <form id="connectSettings" action="/api" method="POST">
        <label for="com">COM Port Address</label>
        <input name="com" type="text">
        <button type="submit">Submit</button>
    </form>
</main>

<style>
    main {
        z-index: 0;
        flex-grow: 100;
        background: white;

        color: black;
        font-size: 16px;

        padding: 20px 40px;
    }

    main form#connectSettings input, main form#connectSettings button {
        border: 1px solid black;
        border-radius: 10px;
        margin: 10px;
        padding: 15px;
    }

    main form#connectSettings input[type=text] {
        outline: none;
    }

    main form#connectSettings input[type=text]:focus {
        box-shadow: 0 0 10px #979797;
    }

    main form#connectSettings button[type=submit] {
        display: inilne-flex;
        align-items: center;

        padding: 15px 20px;
        background: transparent;
        text-transform: uppercase;
        font-family: 'Nunito', sans-serif;
    }

    main form#connectSettings button[type=submit]:hover {
        border-color: #921eff;
        background: linear-gradient(to top, #921eff, #6d1eff);
        color: white;
        box-shadow: 0 0 10px #979797;
    }

    main form#connectSettings button[type=submit]:disabled {
        color: grey !important;
        background: transparent !important;
        box-shadow: none !important;
        border: 1px solid grey !important;
    }
</style>