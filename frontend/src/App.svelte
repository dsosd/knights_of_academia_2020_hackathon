<script>
  import Navbar from "./Navbar.svelte";
  import Main from "./Main.svelte";
  import Footer from "./Footer.svelte";
</script>

<style>
  div#MainWrapper {
    height: 100vh;
    width: -webkit-fill-available;
    display: flex;
    flex-direction: column;
  }
</style>

<div id="MainWrapper">
  <Navbar />
  <Main />
  <Footer />
</div>
