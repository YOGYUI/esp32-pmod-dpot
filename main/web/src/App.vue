<template>
  <div id="app">
    <Header></Header>
    <DPOT></DPOT>
    <Footer></Footer>
  </div>
</template>

<script>
import Header from './components/Header.vue'
import Footer from './components/Footer.vue'
import DPOT from './components/DPOT.vue'

export default {
  components: {
    'Header': Header,
    'Footer': Footer,
    'DPOT': DPOT
  }
}
</script>

<style>
  body {
    text-align: center;
    background-color: white;
  }
  input {
    border-style: groove;
    width: 200px;
  }
  button {
    border-style: groove;
  }
  .shadow {
    box-shadow: 5px 10px 10x rgba(0, 0, 0, 0.03);
  }
</style>
